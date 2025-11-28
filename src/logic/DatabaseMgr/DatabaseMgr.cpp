#include "DatabaseMgr.h"
#include <QCoreApplication>
#include <QThread>



DatabaseMgr::~DatabaseMgr()
{
    closeDatabase();
}

bool DatabaseMgr::initialize()
{
    QMutexLocker locker(&m_mutex);

    if (m_initialized) {
        qWarning() << "Database manager has already been initialized";
        return true;
    }

    // 关闭已存在的连接
    closeDatabase();

    // 获取数据库路径
    QString dbPath = getDatabasePath();
    if (dbPath.isEmpty()) {
        qCritical() << "Failed to get database path";
        return false;
    }

    qInfo() << "Database path:" << dbPath;

    // 创建数据库连接（使用唯一连接名，支持多线程）
    QString connectionName = QString("yume_chat_connection_%1").arg(reinterpret_cast<quintptr>(QThread::currentThreadId()));
    m_database = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    m_database.setDatabaseName(dbPath);

    if (!m_database.open()) {
        qCritical() << "Failed to open database:" << m_database.lastError();
        return false;
    }

    // 设置数据库参数
    if (!setupDatabasePragmas()) {
        qCritical() << "Failed to setup database pragmas";
        closeDatabase();
        return false;
    }

    // 创建表
    if (!createTables()) {
        qCritical() << "Failed to create tables";
        closeDatabase();
        return false;
    }

    m_initialized = true;
    qInfo() << "Database initialized successfully";
    return true;
}

bool DatabaseMgr::setupDatabasePragmas()
{
    QStringList pragmas = {
        "PRAGMA foreign_keys = ON",
        "PRAGMA journal_mode = WAL",
        "PRAGMA synchronous = NORMAL",
        "PRAGMA cache_size = -64000",  // 64MB缓存
        "PRAGMA temp_store = MEMORY"
    };

    for (const QString &pragma : pragmas) {
        if (!execute(pragma)) {
            qCritical() << "Failed to execute pragma:" << pragma;
            return false;
        }
    }
    return true;
}

QString DatabaseMgr::getDatabasePath() const
{
    QString dataPath = QCoreApplication::applicationDirPath();
    QDir dir(dataPath);

    QString dbDirPath = dir.filePath("data");
    QDir dbDir(dbDirPath);

    if (!dbDir.exists() && !dbDir.mkpath(".")) {
        qCritical() << "Failed to create database directory:" << dbDirPath;
        return QString();
    }

    return dir.filePath("data/yume_chat.db");
}

void DatabaseMgr::closeDatabase()
{
    if (m_database.isOpen()) {
        m_database.close();
    }
    m_initialized = false;
}

bool DatabaseMgr::createTables()
{
    QStringList tables;

    tables<<R"(CREATE TABLE IF NOT EXISTS friend_requests
(
    id           INTEGER PRIMARY KEY AUTOINCREMENT,
    sender_id    TEXT NOT NULL,
    recipient_id TEXT NOT NULL,
    status       INTEGER NOT NULL, -- 0=pending, 1=accepted, 2=rejected
    note         TEXT,
    created_at   DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL,
    updated_at   DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL,
    isclose      INTEGER DEFAULT 0 NOT NULL,
    CONSTRAINT uk_friend_request_unique UNIQUE (sender_id, recipient_id)
);)";

    // 好友关系表
    tables << R"(
        CREATE TABLE IF NOT EXISTS friendship(
            id                     INTEGER PRIMARY KEY AUTOINCREMENT,
            local_user_id          TEXT NOT NULL,
            friend_id              TEXT NOT NULL,
            friend_name            TEXT NOT NULL,
            friend_avatar_filepath TEXT NOT NULL,
            created_time           DATETIME DEFAULT CURRENT_TIMESTAMP,
            updated_time           DATETIME DEFAULT CURRENT_TIMESTAMP,
            CONSTRAINT uk_friendship_unique UNIQUE (local_user_id, friend_id)
        )
    )";

    // 消息表 - 优化结构，添加索引
    tables << R"(
        CREATE TABLE IF NOT EXISTS messages (
            id              INTEGER PRIMARY KEY AUTOINCREMENT,
            message_id      TEXT UNIQUE NOT NULL,
            message_type    INTEGER NOT NULL DEFAULT 1,
            sender_id       TEXT NOT NULL,
            conversation_id TEXT NOT NULL,
            message_content TEXT NOT NULL,
            timestamp       BIGINT NOT NULL,
        )
    )";

    for (const QString &sql : tables) {
        if (!execute(sql)) {
            qCritical() << "Failed to create table or index:" << sql;
            return false;
        }
    }

    qInfo() << "Database tables created successfully";
    return true;
}

bool DatabaseMgr::execute(const QString &sql, const QVariantMap &params)
{
    QMutexLocker locker(&m_mutex);

    if (!m_initialized || !m_database.isValid()) {
        qCritical() << "Database is not initialized or valid";
        return false;
    }

    QSqlQuery query(m_database);
    query.prepare(sql);

    // 绑定参数
    for (auto it = params.begin(); it != params.end(); ++it) {
        query.bindValue(":" + it.key(), it.value());
    }

    if (!query.exec()) {
        qCritical() << "SQL execution failed:" << query.lastError()
                   << "SQL:" << sql << "Params:" << params;
        return false;
    }

    return true;
}

QVector<QVariantMap> DatabaseMgr::select(const QString &sql, const QVariantMap &params)
{
    QMutexLocker locker(&m_mutex);
    QVector<QVariantMap> results;

    if (!m_initialized || !m_database.isValid()) {
        qCritical() << "Database is not initialized or valid";
        return results;
    }

    QSqlQuery query(m_database);
    query.prepare(sql);

    for (auto it = params.begin(); it != params.end(); ++it) {
        query.bindValue(":" + it.key(), it.value());
    }

    if (!query.exec()) {
        qCritical() << "Query execution failed:" << query.lastError()
                   << "SQL:" << sql << "Params:" << params;
        return results;
    }

    while (query.next()) {
        QVariantMap record;
        QSqlRecord sqlRecord = query.record();
        for (int i = 0; i < sqlRecord.count(); ++i) {
            record[sqlRecord.fieldName(i)] = query.value(i);
        }
        results.append(record);
    }

    return results;
}

int DatabaseMgr::getLastInsertId()
{
    QMutexLocker locker(&m_mutex);

    if (!m_initialized || !m_database.isValid()) {
        return -1;
    }

    QSqlQuery query("SELECT last_insert_rowid()", m_database);
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }

    return -1;
}

bool DatabaseMgr::transaction()
{
    QMutexLocker locker(&m_mutex);
    return m_database.transaction();
}

bool DatabaseMgr::commit()
{
    QMutexLocker locker(&m_mutex);
    return m_database.commit();
}

bool DatabaseMgr::rollback()
{
    QMutexLocker locker(&m_mutex);
    return m_database.rollback();
}

bool DatabaseMgr::isDatabaseValid() const
{
    QMutexLocker locker(&m_mutex);
    return m_initialized && m_database.isValid() && m_database.isOpen();
}
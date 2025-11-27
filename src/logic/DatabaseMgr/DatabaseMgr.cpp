#include "DatabaseMgr.h"

#include <qcoreapplication.h>

DatabaseMgr &DatabaseMgr::instance()
{
    static DatabaseMgr instance;
    return instance;
}

DatabaseMgr::DatabaseMgr(QObject *parent) : QObject(parent)
{
}

bool DatabaseMgr::initialize()
{
    // 关闭已存在的连接
    if (m_database.isOpen())
    {
        m_database.close();
    }

    // 设置数据库路径
    QString dataPath = QCoreApplication::applicationDirPath();
    QDir dir(dataPath);

    QString dbDirPath = dir.filePath("data");
    QDir dbDir(dbDirPath);
    if (!dbDir.exists())
    {
        dbDir.mkpath(".");
    }
    QString dbPath = dir.filePath("yume_chat.db");

    qDebug() << "数据库路径:" << dbPath;

    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName(dbPath);

    if (!m_database.open())
    {
        qDebug() << "数据库打开失败:" << m_database.lastError();
        return false;
    }

    // 启用外键约束和WAL模式（提高性能）
    execute("PRAGMA foreign_keys = ON");
    execute("PRAGMA journal_mode = WAL");
    execute("PRAGMA synchronous = NORMAL");

    return createTables();
}

bool DatabaseMgr::createTables()
{
    // 用户表
    QStringList tables = {
        // 用户信息表
        "CREATE TABLE IF NOT EXISTS users ("
        "user_id INTEGER PRIMARY KEY, "
        "username TEXT UNIQUE NOT NULL, "
        "email TEXT, "
        "avatar_url TEXT, "
        "created_at DATETIME DEFAULT CURRENT_TIMESTAMP)",

        // 聊天消息表
        "CREATE TABLE IF NOT EXISTS messages ("
        "message_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "sender_id INTEGER NOT NULL, "
        "receiver_id INTEGER NOT NULL, "
        "content TEXT NOT NULL, "
        "message_type INTEGER DEFAULT 0, " // 0:文本, 1:图片, 2:文件
        "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP, "
        "is_read BOOLEAN DEFAULT FALSE, "
        "FOREIGN KEY (sender_id) REFERENCES users (user_id), "
        "FOREIGN KEY (receiver_id) REFERENCES users (user_id))",

        // 好友关系表
        "CREATE TABLE IF NOT EXISTS friendships ("
        "user1_id INTEGER NOT NULL, "
        "user2_id INTEGER NOT NULL, "
        "status INTEGER DEFAULT 0, " // 0:好友, 1:待确认, 2:已拒绝
        "created_at DATETIME DEFAULT CURRENT_TIMESTAMP, "
        "PRIMARY KEY (user1_id, user2_id), "
        "FOREIGN KEY (user1_id) REFERENCES users (user_id), "
        "FOREIGN KEY (user2_id) REFERENCES users (user_id))",

        // 聊天会话表
        "CREATE TABLE IF NOT EXISTS conversations ("
        "conversation_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "user1_id INTEGER NOT NULL, "
        "user2_id INTEGER NOT NULL, "
        "last_message TEXT, "
        "last_message_time DATETIME, "
        "unread_count INTEGER DEFAULT 0)"
    };

    for (const QString &sql: tables)
    {
        if (!execute(sql))
        {
            qDebug() << "创建表失败:" << sql;
            return false;
        }
    }

    qDebug() << "数据库表创建成功";
    return true;
}

bool DatabaseMgr::execute(const QString &sql, const QVariantMap &params)
{
    QSqlQuery query;
    query.prepare(sql);

    for (auto it = params.begin(); it != params.end(); ++it)
    {
        query.bindValue(":" + it.key(), it.value());
    }

    if (!query.exec())
    {
        qDebug() << "SQL执行失败:" << query.lastError() << "SQL:" << sql;
        return false;
    }

    return true;
}

QVector<QVariantMap> DatabaseMgr::select(const QString &sql, const QVariantMap &params)
{
    QVector<QVariantMap> results;

    QSqlQuery query;
    query.prepare(sql);

    for (auto it = params.begin(); it != params.end(); ++it)
    {
        query.bindValue(":" + it.key(), it.value());
    }

    if (!query.exec())
    {
        qDebug() << "查询执行失败:" << query.lastError();
        return results;
    }

    while (query.next())
    {
        QVariantMap record;
        for (int i = 0; i < query.record().count(); ++i)
        {
            QString fieldName = query.record().fieldName(i);
            record[fieldName] = query.value(i);
        }
        results.append(record);
    }

    return results;
}

int DatabaseMgr::getLastInsertId()
{
    QSqlQuery query("SELECT last_insert_rowid()");
    if (query.next())
    {
        return query.value(0).toInt();
    }
    return -1;
}

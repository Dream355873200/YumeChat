#ifndef DATABASEMGR_H
#define DATABASEMGR_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QSqlRecord>
#include <QMutex>

#include "Singleton/Singleton.h"

class DatabaseMgr : public QObject,public Singleton<DatabaseMgr>
{
    Q_OBJECT

public:
    ~DatabaseMgr();

    bool initialize();
    bool execute(const QString& sql, const QVariantMap& params = QVariantMap());
    QVector<QVariantMap> select(const QString& sql, const QVariantMap& params = QVariantMap());
    int getLastInsertId();

    // 新增方法
    bool transaction();
    bool commit();
    bool rollback();
    bool isDatabaseValid() const;

private:
    explicit DatabaseMgr()=default;

    bool createTables();
    bool setupDatabasePragmas();
    QString getDatabasePath() const;
    void closeDatabase();

    QSqlDatabase m_database;
    mutable QMutex m_mutex; // 线程安全
    bool m_initialized = false;
};

#endif // DATABASEMGR_H
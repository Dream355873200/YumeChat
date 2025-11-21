#ifndef DATABASEMGR_H
#define DATABASEMGR_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include<QSqlRecord>
class DatabaseMgr : public QObject
{
    Q_OBJECT

public:
    static DatabaseMgr& instance();
    bool initialize();
    bool execute(const QString& sql, const QVariantMap& params = QVariantMap());
    QVector<QVariantMap> select(const QString& sql, const QVariantMap& params = QVariantMap());
    int getLastInsertId();

private:
    explicit DatabaseMgr(QObject *parent = nullptr);
    bool createTables();
    QSqlDatabase m_database;
};

#endif // DATABASEMGR_H
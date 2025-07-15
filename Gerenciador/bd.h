#ifndef BD_H
#define BD_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class bd
{
public:
    bd(QString path);
    int init();
    int close();

protected:
    static bool create_table(QSqlQuery* query, QString table_name, QString columns) {
        if (!query->exec("CREATE TABLE IF NOT EXISTS " + table_name + "(" + columns + ")")) {
            qDebug() << "Error creating table (" << table_name  << "): " << query->lastError().text();
            return false;
        }
        return true;
    }

private:
    QSqlDatabase db;

};

#endif // BD_H

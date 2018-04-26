#include "lms.h"
#include <QApplication>
#include <QtSql>
#include <QMessageBox>

bool makeConnection();

bool makeConnection()
{
    QSqlDatabase dbLaundry = QSqlDatabase::addDatabase("QSQLITE");

    dbLaundry.setDatabaseName("C:/sqlite/laundry.db");

    if (!dbLaundry.open())
    {
        QMessageBox::critical(0, QObject::tr("Failed to open database"),
                              dbLaundry.lastError().text());
        return false;
    }
    else
        QMessageBox::information(0, "Database", "Database opened");
    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LMS w;
    w.show();

    if (!makeConnection())
        return false;

    return a.exec();
}

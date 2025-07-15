#include "mainwindow.h"
#include "bd.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bd db("database");

    MainWindow w;
    w.show();
    db.close();
    return a.exec();
}



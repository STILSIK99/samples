#include <QCoreApplication>
#include "header.h"
#include "sh.h"
#include <QDebug>

extern int i;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << i;
    change();
    qDebug() << i;
    return a.exec();
}

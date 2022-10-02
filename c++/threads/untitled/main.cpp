#include <QCoreApplication>
#include <QThread>
#include <QObject>
#include <iostream>
#include <QString>
#include "T1.h"
#include "G.h"

using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QThread *q = new QThread;
    T1 * t = new T1;
    G *g = new G;
    g->start(q, t);
    string s;
    while (true){
        cin >> s;
        if (s == "stop"){
            emit g->stop();
            break;
        }
        else{
            emit g->appendString(QString::fromStdString(s));
        }
    }



    return a.exec();
}

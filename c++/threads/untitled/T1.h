#ifndef T1_H
#define T1_H
#include <QObject>
#include <QDebug>
#include <queue>
#include <fstream>
#include <QString>

using namespace std;
class T1 : public QObject
{
    Q_OBJECT

public:
    T1();
    bool work;
    queue<QString> que;

public slots:
    void appendText(QString);
    void thread();
    void stopWork();
};

#endif // T1_H

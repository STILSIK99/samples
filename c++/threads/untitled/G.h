#ifndef G_H
#define G_H
#include <QObject>
#include <QDebug>
#include "T1.h"
#include <QThread>
#include <QString>

class G : public QObject{
    Q_OBJECT
    int k;

public:
    void start(QThread *q, T1 *t){
        t->moveToThread(q);
        connect(this, &G::appendString, t, &T1::appendText);
        connect(this, &G::stop, t, &T1::stopWork);
        connect(q, &QThread::started, t, &T1::thread);
        connect(q, &QThread::finished, t, &T1::deleteLater);
        connect(q, &QThread::finished, t, &T1::deleteLater);
        q->start();
    }


 signals:
    void appendString(QString);
    void stop();

};

#endif // G_H

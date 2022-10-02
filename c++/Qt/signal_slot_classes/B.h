#ifndef B_H
#define B_H
#include <QString>
#include <QWidget>
#include <QObject>

class B : public QObject
{
        Q_OBJECT
        QString a;

    signals:
        void printMes (QString str);

    public:
        B() {}

        void func (QString str)
        {
            emit printMes (str);
        }

};

#endif // B_H

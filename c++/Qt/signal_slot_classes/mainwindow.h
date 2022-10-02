#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QObject>
#include <B.h>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    public slots:
        void print (QString);
    public:
        MainWindow (QWidget *parent = nullptr);
        ~MainWindow();
    private slots:
        void on_pushButton_clicked();

        void on_pushButton_2_clicked();

    private:
        Ui::MainWindow *ui;
        B *b;

};



#endif // MAINWINDOW_H

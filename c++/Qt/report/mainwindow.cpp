#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAxObject>
#include <QDir>
#include <QDebug>

MainWindow::MainWindow (QWidget *parent)
    : QMainWindow (parent)
    , ui (new Ui::MainWindow)
{
    ui->setupUi (this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    try {
        QAxObject   *word = new QAxObject ("Word.Application");
        QAxObject   *documents = word->querySubObject ("Documents");
        //        QAxObject   *doc = documents->querySubObject ("Open(const QString&, bool)", path, true);
        QAxObject *doc = documents->querySubObject ("Add()");
        QAxObject *range = doc->querySubObject ("Range()");
        QAxObject *fonts = range->querySubObject ("Font");

        fonts->setProperty ("Size", 24);
        fonts->setProperty ("Name", "Times New Roman");
        range->dynamicCall ("SetRange(int, int)", 0, 10);
        range->setProperty ("Text", "Обнаружение несоответсвий эталону.");
        QAxObject *tables = doc->querySubObject ( "Tables" );
        QAxObject *table = tables->querySubObject ("Add(Range, NumRows, NumColomns, DefaultTableBehavior, AutoFitBehavior)",
                           range->asVariant(), 8, 2, 1, 2);
        table->querySubObject ( "Cell( Long, Long )", 3, 1)->querySubObject ("Range")->setProperty ("Text", QString ("ячейка"));
        //        cell->setProperty ("Text", "текст таблицы");

        word->setProperty ("Visible", true);
    } catch (...) {
        qDebug() << "some error";
    }
}

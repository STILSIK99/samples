#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::print (QString str)
{
    qDebug() << str;
}


void MainWindow::on_pushButton_clicked()
{
    b = new B;
    connect (b, SIGNAL (printMes (QString)), this, SLOT (print (QString)));
}

void MainWindow::on_pushButton_2_clicked()
{
    b->func ("Hello");
}

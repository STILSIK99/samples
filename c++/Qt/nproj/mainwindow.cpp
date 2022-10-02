#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonObject>

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
    ui->textEdit->clear();
    QJsonObject obj;
    obj["par1"] = "1";
    obj["par2"] = "2";
    obj["par3"] = "3";
    obj["par4"] = "4";
    obj["par5"] = "5";
    obj["par6"] = "6";
}

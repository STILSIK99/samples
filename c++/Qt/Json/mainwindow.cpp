#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QString>

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
    QJsonObject obj;
    obj["encrypt key"] = "abcdef";
    obj["decrypt key"] = "abcdef";
    obj["port"] = 33333;
    QJsonDocument doc (obj);
    QFile f (QDir::currentPath() + "/config.txt");
    f.open (QFile::WriteOnly | QFile::Text);
    f.write (doc.toJson (QJsonDocument::Indented));
    f.close();
    qDebug() << QDir::currentPath();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QDir::currentPath() + "/config.txt";
    QFile jsonFile (fileName);
    jsonFile.open (QFile::ReadOnly);
    ui->textEdit->setText (
        QString (QJsonDocument().fromJson (jsonFile.readAll()).toJson (QJsonDocument::Indented)));
}

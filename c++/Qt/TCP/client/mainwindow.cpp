#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow (QWidget *parent)
    : QMainWindow (parent)
    , ui (new Ui::MainWindow)
{
    ui->setupUi (this);
    tcp_c = new Client (ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    tcp_c->doConnect ("127.0.0.1", 13333);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit->append ("Recieve: " + tcp_c->send_to_server ("Hello, server!"));
}

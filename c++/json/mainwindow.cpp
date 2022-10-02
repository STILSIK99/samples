#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateCmbx();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateCmbx(){
    ui->comboBox->clear();
    ui->comboBox->addItem("Root");
    ui->comboBox->addItems(obj.keys());
};

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_pushButton_2_clicked()
{
    QJsonObject j;
    QJsonObject type;
    QJsonObject pair;
    pair["ip_v4"] = 0x0800;
    type["EtherType"] = pair;
    pair = QJsonObject();
    pair["tcp"] = 0x06;
    pair["udp"] = 0x11;
    type["ip_v4"] = pair;
    pair = QJsonObject();
    pair["http"] = QJsonArray({80, 8080});
    type["tcp"] = pair;
    j["Type"] = type;

    QJsonObject at;
    QJsonArray arr;
    arr.push_back("Destination MAC");
    arr.push_back("Source MAC");
    arr.push_back("Type");
    at["Ethernet"] = arr;

    arr = QJsonArray();
    arr.push_back("Source IP");
    arr.push_back("Destination IP");
    arr.push_back("Protocol");
    at["IP"] = arr;

    arr = QJsonArray();
    arr.push_back("Source port");
    arr.push_back("Destination port");
    at["TCP"] = arr;

    arr = QJsonArray();
//    arr.push_back("POST");
//    arr.push_back("Host");
//    arr.push_back("X-Real-IP");
    arr.push_back("X-Forwarded-For");
//    arr.push_back("X-Forwarded-Proto");
//    arr.push_back("Connection");
//    arr.push_back("Content-Length");
//    arr.push_back("User-Agent");
//    arr.push_back("Accept");
//    arr.push_back("Accept-Language");
//    arr.push_back("Accept-Encoding");
//    arr.push_back("Content-Type");
//    arr.push_back("X-Requested-With");
//    arr.push_back("Origin");
//    arr.push_back("Referer");
//    arr.push_back("Cookie");
    arr.push_back("Via");
    arr.push_back("Username");
    arr.push_back("Password");
//    arr.push_back("Domain");
//    arr.push_back("Authentication");
//    arr.push_back("LogonMsDone");
//    arr.push_back("IsAgentAvailable");
//    arr.push_back("NeedTrySQLLogin");
    at["HTTP"] = arr;

    j["Attibutes"] = at;

    ui->textEdit->setText(
                QJsonDocument(j).toJson());

}

void MainWindow::on_pushButton_3_clicked()
{
    QString file = "D:/Parser tcpdump/proj_qt_vesrion/config.txt";
    QFile f(file);
    f.open(QIODevice::ReadOnly);
    if (!f.isOpen()) return;
    auto obj = QJsonDocument::fromJson(f.readAll()).object();
    ui->textEdit->setText(QJsonDocument(obj).toJson());
}

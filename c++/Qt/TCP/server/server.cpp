#include "server.h"

Server::Server (QWidget *parent) : QWidget (parent) {};

bool Server::initServer (int port, QTextEdit *t)
{
    te = t;
    server = new QTcpServer;
    if (!server->listen (QHostAddress::Any, port)) {
        QMessageBox::critical (nullptr,
                               "Server Error",
                               "Unable to start the server:"
                               + server->errorString());
        server->close();
        return false;
    }
    this->port = port;
    connect (server, SIGNAL (newConnection()), this, SLOT (slotNewConnection()));
    block = 0;
    return true;
};

void Server::slotNewConnection()
{
    QTcpSocket *sock = server->nextPendingConnection();

    connect (sock, SIGNAL (readyRead()),
             this, SLOT (slotReadClient()));

    connect (sock, SIGNAL (disconnected()),
             sock, SLOT (deleteLater()));

    sendToClient (sock, "Server connected!");
};

QString Server::slotReadClient()
{
    QTcpSocket *sock = (QTcpSocket *)sender();
    QDataStream in (sock);
    in.setVersion (QDataStream::Qt_5_7);
    while (true) {
        if (!block) {
            if (sock->bytesAvailable() < sizeof (quint16)) {
                break;
            }
            in >> block;
        }

        if (sock->bytesAvailable() <= block) {
            break;
        }
    }
    QString str;
    in >> str;
    QString strMess = " Client has sent: " + str;
    block = 0;
    //    qDebug() << strMess;
    te->append (strMess);
    sendToClient (sock, "Server received message!");
    return strMess;
}

void Server::sendToClient (QTcpSocket *sock, const QString &str)
{
    QByteArray arrBlock;
    QDataStream out (&arrBlock, QIODevice::WriteOnly);
    out.setVersion (QDataStream::Qt_5_7);
    out << quint16 (0) << str;

    out.device()->seek (0);
    out << (quint16 (arrBlock.size()) - sizeof (quint16));
    sock->write (arrBlock);
}

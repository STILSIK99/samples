#include "client.h"

Client::Client (QTextEdit *t, QWidget *parent) : QWidget (parent), te (t) {};

bool Client::doConnect (QString host, int port)
{
    block = 0;
    client = new QTcpSocket (this);
    client->connectToHost (host, port);
    connect (client, SIGNAL (connected()), SLOT (slotConnected()));
    connect (client, SIGNAL (readyRead()), SLOT (slotReadyRead()));
    connect (client, SIGNAL (error (QAbstractSocket::SocketError)),
             this,         SLOT (slotError (QAbstractSocket::SocketError)));
    //    send_to_server (str);
};

QString Client::slotReadyRead (bool a = false)
{
    //    QString str = client->readAll();
    QDataStream in (client);
    in.setVersion (QDataStream::Qt_5_7);
    for (;;) {
        if (!block) {
            if (client->bytesAvailable() < sizeof (quint16)) if (!a && client->bytesAvailable() == 0) break;
            in >> block;
        }
        if (client->bytesAvailable() < block) if (!a && client->bytesAvailable() == 0) break;
        QString str;
        in >> str;
        block = 0;
        //        te->append (str);
        //        qDebug() << str << "\n";
        return str;
    }
    return "";
}

void Client::slotError (QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString (client->errorString())
                    );
    //    qDebug() << strError;
    te->append (strError);
    te->append (client->errorString());
    //    qDebug() << client->errorString();
    qDebug() << "\n";
}

QString Client::send_to_server (QString str)
{
    QByteArray  arrBlock;
    QDataStream out (&arrBlock, QIODevice::WriteOnly);
    out.setVersion (QDataStream::Qt_5_7);
    out << quint16 (0) << str;
    out.device()->seek (0);
    out << quint16 (arrBlock.size() - sizeof (quint16));
    client->write (arrBlock);
    return slotReadyRead (true);
}

void Client::slotConnected()
{
    //    te->append ("Received the connected() signal");
    //    qDebug() << "Received the connected() signal";
}

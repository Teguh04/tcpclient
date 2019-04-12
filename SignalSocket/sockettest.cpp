#include "sockettest.h"

SocketTest::SocketTest(QObject *parent) :
    QObject(parent)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()),Qt::DirectConnection);
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
}

void SocketTest::Test()
{
    qDebug() << "Connecting,..";

    //socket->connectToHost("ais.solusi247.com", 4200);
    //socket->connectToHost("52.20.16.20", 30001);
    socket->connectToHost("192.168.6.140", 1234);


    if(!socket->waitForDisconnected(1000))
    {
        qDebug() << "Error: " << socket->errorString();
    }
}

void SocketTest::connected()
{
    qDebug() << "Connected!";

    //socket->write(QString("/me-client: client_tcp_test \n").toUtf8());
    socket->write("client_tcp_test");

    socket->flush();
    socket->waitForBytesWritten(1000);
}

void SocketTest::disconnected()
{
    qDebug() << "Disconnected!";
}

void SocketTest::bytesWritten(qint64 bytes)
{
    qDebug() << "We wrote: " << bytes;
}

void SocketTest::readyRead()
{
    //qDebug() << "Reading...";
    qDebug() << socket->readAll();
    socket->flush();
}


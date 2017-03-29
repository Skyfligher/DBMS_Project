#include "connectionhandle.h"

connectionHandle::connectionHandle(QObject *parent, int port) : QObject(parent)
{
    server = new QTcpServer(this);
    server ->listen(QHostAddress::Any,port);

}
connectionHandle::connectionHandle(int port){
    server = new QTcpServer(this);
    server ->listen(QHostAddress::Any,port);
}

QByteArray connectionHandle::handle(){
        QByteArray data;
        server->waitForNewConnection(1000);
    if(server->hasPendingConnections()){
        qDebug() << "has pending connection!";
        socket = server->nextPendingConnection();
        qDebug() << "socket setup!";
        data.resize(socket->readBufferSize());
        socket->waitForReadyRead(1000);
        data = socket->readAll();
        qDebug() << "socket read!" << data;
        socket->write("1");
        socket->waitForBytesWritten(10);
        qDebug() << "confirmation sent!";
        socket->abort();
        qDebug() << "socket aborted";
        return  data;
    }

    else {
    data.resize(1);
    data[0] = 0;
        return data;
}}
void connectionHandle::sessionOpen(){
    socket = server->nextPendingConnection();

}

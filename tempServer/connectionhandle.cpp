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

QString connectionHandle::handle(){
        QString data;
       server->waitForNewConnection(1000);
    if(server->hasPendingConnections()){
        qDebug() << "has pending connection!";
        socket = server->nextPendingConnection();
        qDebug() << "socket setup!";
        data.resize(socket->readBufferSize());
        socket->waitForReadyRead(1000);
        data = socket->readAll();
        qDebug() << "socket read!" << data;
        return  data;
    }

    else {
    QString data;
        return data;
}}
void connectionHandle::sessionOpen(){
    socket = server->nextPendingConnection();

}

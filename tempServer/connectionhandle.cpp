#include "connectionhandle.h"
/*                          Handles all the connections
 * Removes copious amounts of code from the main program, handles all the server object functions in the background.
 */

connectionHandle::connectionHandle(QObject *parent, int port) : QObject(parent)     //Constructor
{
    server = new QTcpServer(this);                  //Creates a new server object to listen for connections
    server ->listen(QHostAddress::Any,port);        //Starts the server listening on port given, accepts from any host address (IP Address)

}
connectionHandle::connectionHandle(int port){       //Constructor without the QObject being needed
    server = new QTcpServer(this);                  //Creates a new server object to listen for connections
    server ->listen(QHostAddress::Any,port);        //Starts the server listening on port given, accepts from any host address (IP Address)
}

QStringList connectionHandle::handle(){             //Function listens for incoming connections
    QString data;                                   //Buffer for incoming data
    if(server->hasPendingConnections())             //If server has a connection waiting
    {
        socket = server->nextPendingConnection();   //Creates socket to the pending connection address
        data.resize(socket->readBufferSize());      //Resizes data to the incoming buffer size, how much data is being sent
        socket->waitForReadyRead(1000);             //Waiting to read
        data = socket->readAll();                   //Reads the incoming data into QString
        QStringList dataList = data.split(',');     //Parsing the data into a QStringList by commas
        return  dataList;                           //Returns the dataList
    }

    else {
        QStringList data;   //Creates empty QStringList
        data<<"";           //Makes an empty string in the list
        return data;        //Returns empty string failed status
    }
}


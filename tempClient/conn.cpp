#include "conn.h"
#include "ui_conn.h"
#include <QMainWindow>
#include <QMouseEvent>
#include <QMessageBox>
#include <QTcpSocket>

conn::conn(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::conn)
{
    ui->setupUi(this);              //Sets up the ui for login, using Ui::Login -> the login form
}

conn::~conn()                       //Removes the ui without ending the window process, hides it
{
    delete ui;
}

void conn::mousePressEvent(QMouseEvent *event) //Triggers event when mouse clicks window
{
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void conn::mouseMoveEvent(QMouseEvent *event) //Moves window with mouse when clicked
{
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}


void conn::on_pushButton_clicked()              //On test button clicked
{
    socket = new QTcpSocket();                  //Creates new socket
    socket->connectToHost("127.0.0.1",1000);    //Uses home ip address and port 1000
    if(socket->waitForConnected(10000))         //Waiting for connection to server
    {
        if(socket->state() == QAbstractSocket::ConnectedState)  //Makes sure the socket is connected before writing
        {
            socket->write("1,");                //Writes a 1 to indicate it is connected, server returns a 1. the comma is for the servers parser
            socket->waitForBytesWritten(1000);  //Waits a second for the bytes to be written
            socket->waitForReadyRead(1000);     //Waits a second for the reply
            if(socket->readAll() == "1")        //Checks reply for an acknowlegement
            {
                emit closeConn("127.0.0.1", 1000);  //Signals the main window that the connection window is closing, and sends host id and port number
                socket->abort();                    //Aborts the socket before closing
                this->close();                      //Closes this window
            }
            else
            {
                QMessageBox::information(this, "Server", "Not Connected."); //Error message
            }

        }
        else
        {
            QMessageBox::information(this, "Server", "Not connected.");     //Error message
        }

        socket->abort();    //Aborts the socket
    }
    else
    {
        QMessageBox::information(this, "Server", "Not connected.");         //Error message
    }
    socket->abort();        //Aborts the socket
}

void conn::on_pushButton_2_clicked()            //Connect button clicked
{
    QString host;
    if(ui->lineEdit->text() != "" && ui->lineEdit_2->text() != "")          //Checking if the textboxes have information
    {
        host = ui->lineEdit->text();    //Takes host address from the corrisponding textbox
        bool ok;                        //Checking if text in the port box is a number
        ui->lineEdit_2->text().toInt(&ok);  //Checking if number to bool at &ok
        if(ok)                              //True if a number
        {
            if(ui->lineEdit_2->text().toInt() != 0) //True if port larger than 0, must be larger than 0
            {
                int port = ui->lineEdit_2->text().toInt();  //Setting port = to what is in the text box
                socket = new QTcpSocket();                  //Opening a new socket
                socket->connectToHost(host,port);           //Connecting with provided information
                if(socket->waitForConnected(10000))         //Waiting for a connection for 10 seconds else giving error
                {
                    if(socket->state() == QAbstractSocket::ConnectedState)  //Making sure that connection is still up
                    {
                        socket->write("1,");                //Asking for acknowledgment
                        socket->waitForBytesWritten(10);    //Waiting for bytes to be written
                        socket->waitForReadyRead(1000);     //Waiting for response for a second
                        if(socket->readAll() == "1")        //If response
                        {
                            socket->abort();            //Aborting socket
                            emit closeConn(host,port);  //Sending signal to open login window
                            this->close();              //Closing this window
                        }
                    }

                }
                else
                {
                    QMessageBox::information(this, "Server", "Not connected.");                                 //Giving out error
                }
            }
            else
            {
                socket->abort();    //Aborting socket
                QMessageBox::information(this, "Error", "You must enter a valid port number");                  //Giving out error
            }
        }
        else if(ui->lineEdit->text() == "")                                     //Checking if error on host adress
        {
            QMessageBox::information(this, "Error", "You must enter a valid host address.");                    //Giving out error
        }
        else                                                                    //Only a port address error left
        {
            QMessageBox::information(this, "Error", "You must enter a valid port number.");                     //Giving out error
        }
    }
    else                                                                        //Port textbox does not contain a number
    {
        QMessageBox::information(this, "Error", "You must enter a valid host address and port number.");        //Giving out error
    }
}

void conn::on_pushButton_3_clicked()            //When exit button clicked
{
    emit mainClose();   //Signals main window to close
    this->close();      //Closes this window
}

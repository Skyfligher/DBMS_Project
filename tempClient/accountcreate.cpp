#include "accountcreate.h"
#include "ui_accountcreate.h"
#include <QMainWindow>
#include <QMouseEvent>
#include <QMessageBox>
#include <QTcpSocket>

accountCreate::accountCreate(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::accountCreate)
{
    ui->setupUi(this);      //Setting up ui based on accountCreate form
}

accountCreate::~accountCreate() //Ends the window without ending the process
{
    delete ui;
}
accountCreate::accountCreate(QString host, int port)    //Constructor need the host address and port number
{
    this->host = host;  //Setting variables
    this->port = port;
}

void accountCreate::mousePressEvent(QMouseEvent *event) //Triggers event when mouse clicks window
{
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void accountCreate::mouseMoveEvent(QMouseEvent *event)  //Moves window with mouse when clicked
{
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

void accountCreate::on_pushButton_clicked() //When create account is clicked
{
    QString username = ui->lineEdit->text();    //Taking info from the username text box
    QString email = ui->lineEdit_2->text();     //Taking info from the email text box
    QString first = ui->lineEdit_3->text();     //Taking info from the first name text box
    QString last = ui->lineEdit_4->text();      //Taking info from the last name text box
    QString password = ui->lineEdit_5->text();  //Taking info from the password text box

    if(username != "" && email != "" && first != "" && last != "" && password != "")    //Checks if all the text boxes are filled
    {
        QString temp = "3,"+username+","+email+","+first+","+last+","+password; //Writing the string that will be sent, the commas are used for the servers parsing
        socket = new QTcpSocket();                          //Opeing a new socket
        socket->connectToHost(this->host,this->port);       //Connecting to host with the information in the window
        if(socket->waitForConnected(1500))                  //Waiting for connection
        {
            if(socket->state() == QAbstractSocket::ConnectedState)  //Making sure of connection
            {
                socket->write(temp.toUtf8());               //Writing to the socket, .toUtf8 takes the QString into a byte array
                socket->waitForBytesWritten(10);            //Waiting for bytes to be written
                socket->waitForReadyRead(1500);             //Waiting for reply
                QString acknowleged = socket->readAll();    //Reading acknowlegement
                if(acknowleged.toInt() == 1)                //Checking for errors, will = 1 if it was completed
                {
                    emit usercreate(acknowleged);   //Signals the main window that a user was created, opeing up the login window
                    socket->abort();                //Closing socket
                    this->close();                  //Closing the create user window
                }
                else
                {
                    QMessageBox::information(this, "Error", "There was a database error, try again later.");    //Giving error
                }

            }

        }
    }
    else
    {
        QMessageBox::information(this, "Error", "You must fill out every space.");                              //Giving error
    }
}



void accountCreate::on_pushButton_2_clicked()   //When login button click
{
    emit gotoLog("1");  //Signaling main window to open the login window
    this->close();      //Closing this window, ending the process
}

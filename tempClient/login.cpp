#include "login.h"
#include "ui_login.h"
#include <QMainWindow>
#include <QMouseEvent>
#include <QMessageBox>
#include <QTcpSocket>


login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);  //Sets up the ui for login, using Ui::Login -> the login form
}

login::~login()     //Removes the ui without ending the window process, hides it
{
    delete ui;
}

void login::mousePressEvent(QMouseEvent *event) //Triggers event when mouse clicks window
{
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void login::mouseMoveEvent(QMouseEvent *event) //Moves window with mouse when clicked
{
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}



void login::on_pushButton_2_clicked()   //Takes the given email and password and passes it along to the server, the server checks and acknowleges
{
    if(ui->lineEdit->text() != "" && ui->lineEdit_2->text() != "")  //Makes sure there is information in the textboxes
    {
        QString temp = "2,"+ui->lineEdit->text()+","+ui->lineEdit_2->text();
                                                        //Builds string to send to server uses 2 to indicate what operation the server should run, check user login info
                                                        //Takes the text from the email text box, lineEdit
                                                        //Takes the text from the password text box, lineEdit_2

        QByteArray send = temp.toUtf8();                //Takes the qstring and converts it to a bytearray that can be sent through the socket
        socket = new QTcpSocket();                      //Creates new socket
        socket->connectToHost(host,port);               //Connects to the server using the credentials given by the connection screen
        if(socket->waitForConnected(1500))              //Waits 1500ms for the connection
        {
            if(socket->state() == QAbstractSocket::ConnectedState)  //checks if the socket is connected
            {
                socket->write(send);                //Writes the bytearray
                socket->waitForBytesWritten(10);    //Waits for it to finish writing
                socket->waitForReadyRead(1500);     //Waits for reply
                QString userID = socket->readAll(); //Reads the socket into userID string
                socket->abort();                    //Deletes the socket

                if(userID != "failedPass" && userID != "failedEmail" && userID != "databaseError")   //Tests for failed Email, Password, or database error
                {
                    emit closeLog(userID.toInt());      //Opens the mainwindow sending the userID to it
                    this->close();                      //Closes the login window, ending the window
                }
                else
                {
                    if(userID == "failedEmail")
                    {
                        QMessageBox::information(this,"Error", "Your email was not found.");      //Messages failed email
                    }
                    else if(userID == "failedPass")
                    {
                        QMessageBox::information(this, "Error", "Your password is not correct.");   //Messages failed password
                    }
                    else
                    {
                        QMessageBox::information(this, "Error", "There was a database error, try again later"); //Database error
                    }
                }
            }
        }
    }
    else if(ui->lineEdit->text() == "" && ui->lineEdit_2->text() == "")
    {
        QMessageBox::information(this, "Error", "Please enter a valid Email Address and Password"); //If there is no information in either textbox
    }
    else if(ui->lineEdit->text() == "")
    {
        QMessageBox::information(this, "Error", "Please enter a valid Email Address");              //If there is no information in the email textbox
    }
    else
    {
        QMessageBox::information(this, "Error", "Please enter a valid Password");                   //If there is no information in the password textbox
    }

}

void login::on_pushButton_clicked()             //When create account clicked
{
    emit createAccount();                       //Tells mainwindow to open accountcreate
    this->hide();                               //Hides the login window, does not end the window
}
void login::creatuser(QString aknowlege)        //Checks if the create account was successful or if the login button was pressed
{
    if(aknowlege == "1")                        //If 1 the account was created or the login button was pressed
    {
        this->show();                           //Show the window
    }
}


void login::on_pushButton_3_clicked()           //On exit button pushed
{
    emit mainClose();                           //Sends signal to close the main window
    this->close();                              //Closes the login window

}

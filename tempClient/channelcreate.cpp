#include "channelcreate.h"
#include "ui_channelcreate.h"
#include <QMainWindow>
#include <QMouseEvent>
#include <QMessageBox>
#include <QTcpSocket>


channelcreate::channelcreate(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::channelcreate)
{
    ui->setupUi(this);
}

channelcreate::~channelcreate()
{
    delete ui;
}

void channelcreate::on_pushButton_2_clicked()       //Exits and closes the window, back to main window
{
    this->close();
}

void channelcreate::mousePressEvent(QMouseEvent *event) //Triggers event when mouse clicks window
{
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void channelcreate::mouseMoveEvent(QMouseEvent *event)  //Moves window with mouse when clicked
{
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

void channelcreate::on_pushButton_clicked()             //Sends info to create window
{
    QString temp = "4,"+ui->lineEdit->text()+","+ui->textEdit->toPlainText();
                                                       //Builds string to send, taking the name and the discription from the textboxes
    QByteArray send = temp.toUtf8();                    //Converting to a Utf8 byte array for tcp sending
    socket = new QTcpSocket();
    socket->connect(host,port);

















}

#include "accountcreate.h"
#include "ui_accountcreate.h"

accountCreate::accountCreate(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::accountCreate)
{
    ui->setupUi(this);
}

accountCreate::~accountCreate()
{
    delete ui;
}
accountCreate::accountCreate(QString host, int port){
    this->host = host;
    this->port = port;
}

void accountCreate::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void accountCreate::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

void accountCreate::on_pushButton_clicked()
{
    QString username = ui->lineEdit->text();
    QString email = ui->lineEdit_2->text();
    QString first = ui->lineEdit_3->text();
    QString last = ui->lineEdit_4->text();
    QString password = ui->lineEdit_5->text();

    QString temp = "3,"+username+","+email+","+first+","+last+","+password;
    QByteArray send = temp.toUtf8();
    socket = new QTcpSocket();
    socket->connectToHost(this->host,this->port);
    if(socket->waitForConnected(1500)){
        if(socket->state() == QAbstractSocket::ConnectedState){
            socket->write(send);
            socket->waitForBytesWritten(10);
            socket->waitForReadyRead(1500);
            QString aknowleged = socket->readAll();
            emit usercreate(aknowleged);
            socket->abort();
            this->close();

        }

    }
}



void accountCreate::on_pushButton_2_clicked()
{
    emit gotoLog("1");
    this->close();
}

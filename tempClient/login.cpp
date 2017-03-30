#include "login.h"
#include "ui_login.h"



login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void login::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}






void login::on_pushButton_2_clicked()
{
    QString email = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QString temp = "2,"+email+","+password;
    QByteArray send = temp.toUtf8();
    socket = new QTcpSocket();
    socket->connectToHost(host,port);
    if(socket->waitForConnected(1500)){
        if(socket->state() == QAbstractSocket::ConnectedState){
            socket->write(send);
            socket->waitForBytesWritten(10);
            socket->waitForReadyRead(1500);
            QString userID = socket->readAll();
            emit Want2CloseLog(userID.toInt());
            socket->abort();
            this->close();

        }

    }
}

void login::on_pushButton_clicked()
{
    emit createAccount();
    this->hide();
}
void login::creatuser(QString aknowlege){
    if(aknowlege == "1"){
        this->show();
    }
}


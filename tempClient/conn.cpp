#include "conn.h"
#include "ui_conn.h"


conn::conn(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::conn)
{
    ui->setupUi(this);
}

conn::~conn()
{
    delete ui;
}

void conn::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void conn::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}


void conn::on_pushButton_clicked()
{
    socket = new QTcpSocket();
    socket->connectToHost("127.0.0.1",1000);
    if(socket->waitForConnected(10000)){
        if(socket->state() == QAbstractSocket::ConnectedState){
            socket->write("1,");
            socket->waitForBytesWritten(1000);
            socket->waitForReadyRead(1000);
            if(socket->readAll() == "1"){
                emit Want2Close("127.0.0.1", 1000);
                this->close();
            }

        }
        else{
            QMessageBox::information(this, "Server", "Not connected.");
        }

        socket->abort();
    }
}

void conn::on_pushButton_2_clicked()
{
    QString host = "";
    host = ui->lineEdit->text();
    int port = ui->lineEdit_2->text().toInt();
    if(port > 0 && host != ""){
        socket = new QTcpSocket();
        socket->connectToHost(host,port);
        if(socket->waitForConnected(10000)){
            if(socket->state() == QAbstractSocket::ConnectedState){
                socket->write("1,");
                socket->waitForBytesWritten(10);
                socket->waitForReadyRead(1000);
                if(socket->readAll() == "1"){
                    emit Want2Close(host,port);
                    this->close();
                }
            }

        }
        else{
            QMessageBox::information(this, "Server", "Not connected.");
        }
        socket->abort();
    }
}

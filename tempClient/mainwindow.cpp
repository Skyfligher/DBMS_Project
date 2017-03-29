#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_login.h"
#include <QMouseEvent>
#include <QMessageBox>
#include <QTcpSocket>
#include <QWidget>

QTcpSocket *socket;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}



MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}


void MainWindow::on_testButton_clicked()
{
    socket = new QTcpSocket();
    socket->connectToHost("127.0.0.1",1000);
    if(socket->waitForConnected(10000)){
        QMessageBox::information(this,"Server", "Connected!!!");

        if(socket->state() == QAbstractSocket::ConnectedState){
            socket->write("1:;:");
            socket->waitForBytesWritten(1000);
            QMessageBox::information(this, "Info", "Bytes Written!");
        }

    }
    else{
        QMessageBox::information(this, "Server", "Not connected.");
    }

    socket->abort();
}



void MainWindow::on_connectButton_clicked()
{
    socket = new QTcpSocket(this);
    socket->connectToHost("192.168.0.100",1000);
    if(socket->waitForConnected(1000)){

        if(socket->state() == QAbstractSocket::ConnectedState){
            socket->write("1:;:");
            socket->waitForBytesWritten(10);
            socket->waitForReadyRead(1000);
            if(socket->readAll() == "1"){
                //hide();
                QDialog *wig = new QDialog;

            Ui::Login log;
            log.setupUi(wig);
            wig->show();
            hide();
            }
        }

    }
    else{
        QMessageBox::information(this, "Server", "Not connected.");
    }

    socket->abort();

}

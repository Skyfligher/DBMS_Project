#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    log.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    //log.show();

    con.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    con.show();

    QMainWindow::connect(&con, SIGNAL(Want2Close(QString, int)), this, SLOT(showLog(QString, int)));
    QMainWindow::connect(&log, SIGNAL(Want2CloseLog(int)), this, SLOT(showMain(int)));
    QMainWindow::connect(&log, SIGNAL(createAccount()), this, SLOT(createAcc()));
    QMainWindow::connect(&acct, SIGNAL(gotoLog(QString)), &log, SLOT(creatuser(QString)));
    QMainWindow::connect(&acct, SIGNAL(usercreate(QString)), &log, SLOT(creatuser(QString)));
  //  connect(log, &login::Want2Close, this, &MainWindow::show());
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

void MainWindow::showLog(QString temphost, int tempport){
    host = temphost;
    port = tempport;
    log.host = temphost;
    log.port = tempport;
    log.show();
}

void MainWindow::showMain(int userId){
    this->show();
    QString user = QString::number(userId);
}

void MainWindow::createAcc(){
    acct.host = host;
    acct.port = port;
    acct.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    acct.show();
}

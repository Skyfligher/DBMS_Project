#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QMouseEvent>
#include <QMessageBox>
#include <QTcpSocket>
#include <QDate>

/* Things to do
 * Change parser to something other than a comma no :or;
 * Add the Channels and Channel Id tables
 *      channelid(time, message, sender) the ID in channelid should be the channels given id (channel1,channel35,exd
 * Function to create linked list of messages, it should create new items in the List Widget(need to learn how to add them)
 * Function to get data from the server and put it into the linked list (need ability to apend to the top of the list and add to list widget)
 *      once the widget is scrolled to top must load older messages.
 * Need server function to search for the requested messages based on time.
 * Need server function to update all connected clients when a message is sent. Connected users should be kept in an array on both the client and server.
 *
*/


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    log.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);   //Sets login window to frameless mode, asthetics

    con.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);   //Sets connection window to frameless mode, asthetics
    con.show();  //Shows the connection window

    QMainWindow::connect(&con, SIGNAL(closeConn(QString, int)), this, SLOT(showLog(QString, int))); //connecting signal emited when connected to server to show login
    QMainWindow::connect(&log, SIGNAL(closeLog(int)), this, SLOT(showMain(int)));   //connecting signal emitted when logged in succesfully, opens main window and sets user id
    QMainWindow::connect(&log, SIGNAL(createAccount()), this, SLOT(createAcc()));   //connects signal emitted by create account button to close login and open accountcreate
    QMainWindow::connect(&acct, SIGNAL(gotoLog(QString)), &log, SLOT(creatuser(QString)));  //Takes user back to the login screen
    QMainWindow::connect(&acct, SIGNAL(usercreate(QString)), &log, SLOT(creatuser(QString)));   //when gotoLog() is emitted creatuser() checks for aknowlegment then opens login if succesful
    QMainWindow::connect(&log, SIGNAL(mainClose()), this, SLOT(mainClosed()));  //Closes client when mainClose() is emitted (must close the active window after emitting
}
MainWindow::~MainWindow()   //exits the ui without ending the process, can reopen the window
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)    //Triggers event when mouse clicks window
{
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)     //Moves window with mouse when clicked
{
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

void MainWindow::showLog(QString temphost, int tempport)    //Takes info from signal(when connected to server) sets the host address and port number for the main window and login window
{
    host = temphost;
    port = tempport;
    log.host = temphost;
    log.port = tempport;
    log.show();                                         //Opens the loging window
}

void MainWindow::showMain(int userIdtemp)   //Takes info from signal(logged in) and sets the userid
{
    this->show();
    useId = userIdtemp;                     //Sets user id

    socket = new QTcpSocket();
    socket->connectToHost(host,port);
    if(socket->waitForConnected(1500))
    {
        socket->write("4");
        socket->waitForBytesWritten(100);

        if(socket->waitForReadyRead(1500))
        {
            QString data = socket->readAll();
            QStringList dataList = data.split(',');
            for(int t = 0; t < dataList.size(); t++)
            {
                chat<<dataList.at(t);
                ui->textBrowser->append("\n"+dataList.at(t));
            }
        }
        socket->abort();
    }
    else
    {
        QMessageBox::information(this,"Error","Cannot connect to the server.");
    }
    //socket->connectToHost(host,port);
    while(socket->state() == QAbstractSocket::ConnectedState)
    {
        qDebug()<<"Listening";
        if(socket->waitForReadyRead(1500))
        {

            QString data = socket->readAll();
            QStringList dataList = data.split(',');
            for(int t = 0; t < dataList.size(); t++)
            {
                chat<<dataList.at(t);
                ui->textBrowser->append("\n"+dataList.at(t));
            }
        }
    }
}

void MainWindow::createAcc()    //Triggered by signal(create account button) and sets the windows host info and then shows the window
{
    acct.host = host;
    acct.port = port;
    acct.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);  //Sets the window to frameless mode, asthetics
    acct.show();
}

void MainWindow::on_Exit_Button_clicked()   //Exits the program closes this window on exit button press
{
    this->close();
}

void MainWindow::mainClosed()   //Exits the program when triggered by signal(mainClose()) ends the program
{
    this->close();
}



void MainWindow::on_lineEdit_returnPressed()
{
    socket = new QTcpSocket();
    socket->connectToHost(host,port);
    if(socket->waitForConnected(1500))
    {
        QString tempMessage = "5,"+ QString::number(useId) +","+ui->lineEdit->text();
        if(socket->write(tempMessage.toUtf8()))
        {
            socket->waitForBytesWritten(150);
            QDateTime temp = temp.currentDateTime();
            chat<< "<ME "+temp.toString("dd.MM.yyyy HH:mm:ss")+"> "+ui->lineEdit->text();
            ui->textBrowser->append("\n<ME "+temp.toString("dd.MM.yyyy HH:mm:ss")+"> "+ui->lineEdit->text());
            socket->abort();
        }
    }
}

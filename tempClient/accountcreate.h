#ifndef ACCOUNTCREATE_H
#define ACCOUNTCREATE_H

#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class accountCreate;                                //Creating class name
}

class accountCreate : public QMainWindow
{
    Q_OBJECT

public:
    explicit accountCreate(QWidget *parent = 0);    //Creating application widget
    accountCreate(QString host, int port);          //Class constructor, takes the host address and port number
    ~accountCreate();                               //Class destructor
    QString host;                                   //Host address
    int port;                                       //Port number

private slots:
    void on_pushButton_clicked();       //Slot for the create account button click
    void on_pushButton_2_clicked();     //Slot for the login button click

signals:
    void gotoLog(QString akn);          //Signals to close window and reopen the hidden login window
    void usercreate(QString akn);       //Signals that the account was created closing the window and opening the login window


private:
    Ui::accountCreate *ui;                          //Creating Ui::accountCreate from accountCreate.ui form
    void mousePressEvent(QMouseEvent *event);       //For click and drag functionality on window
    void mouseMoveEvent(QMouseEvent *event);        //
    int m_nMouseClick_X_Coordinate;                 //
    int m_nMouseClick_Y_Coordinate;                 //
    QTcpSocket *socket;                             //Creates a socket for server communication


};

#endif // ACCOUNTCREATE_H

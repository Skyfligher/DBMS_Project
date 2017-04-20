#ifndef CONN_H
#define CONN_H

#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class conn;                                     //Setting class name
}

class conn : public QMainWindow
{
    Q_OBJECT

public:
    explicit conn(QWidget *parent = 0);         //Creating application widget
    ~conn();                                    //Destructor

private slots:
    void on_pushButton_clicked();               //Slot for test button click
    void on_pushButton_2_clicked();             //Slot for connect button click
    void on_pushButton_3_clicked();             //Slot for exit button click

private:
    Ui::conn *ui;                               //Create the Ui::conn using the conn.ui form
    void mousePressEvent(QMouseEvent *event);   //Click and drag for the window
    void mouseMoveEvent(QMouseEvent *event);    //
    int m_nMouseClick_X_Coordinate;             //
    int m_nMouseClick_Y_Coordinate;             //
    QTcpSocket *socket;                         //Creating socket for server connection

signals:
    void closeConn(QString host, int port);     //Signal that closes the window and opens the login function
    void mainClose();                           //Closes the window and signals the mainwindow to close
};

#endif // CONN_H

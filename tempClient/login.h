#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class login;                                    //Setting class name
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);        //Creating login application widget
    ~login();                                   //Widget destructor
    QString host;                               //String for the host address
    int port;                                   //Integer for the port number

private slots:
    void on_pushButton_2_clicked();             //The login buttons slot when clicked, attempts to login to the server
    void on_pushButton_clicked();               //The create account buttons slot when clicked, opens the create user account
    void creatuser(QString aknowlege);          //Slot that when activated opens the window, when user is created or when the login button is pressed from create account window
    void on_pushButton_3_clicked();             //The exit buttons slot that closes the window and the program by signaling the main windwo close slot

private:
    Ui::login *ui;                              //Creating the Ui::login using the login.ui
    void mousePressEvent(QMouseEvent *event);   //For click and drag window properties
    void mouseMoveEvent(QMouseEvent *event);    //
    int m_nMouseClick_X_Coordinate;             //
    int m_nMouseClick_Y_Coordinate;             //
    QTcpSocket *socket;                         //Socket for talking to the server

signals:
    void closeLog(int useId);       //Closes the login window and sends userId to the main window
    void createAccount();           //Hides the login window and opens the create account window
    void mainClose();               //Signals the close of the main window, closes the program
};

#endif // LOGIN_H

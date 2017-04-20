#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <conn.h>
#include <login.h>
#include <accountcreate.h>


namespace Ui {
class MainWindow;                                       //Setting class name
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);           //Creating a mainwindow widget
    ~MainWindow();                                      //Main window destructor
    QString host;                                       //Host address
    int port;                                           //Port number
    int useId;                                          //UserId, will be used for most functions. Provided by the login window

private:
    Ui::MainWindow *ui;                                 //Setting up the Ui::MainWindow
    void mousePressEvent(QMouseEvent *event);           //For window click and drag
    void mouseMoveEvent(QMouseEvent *event);            //
    int m_nMouseClick_X_Coordinate;                     //
    int m_nMouseClick_Y_Coordinate;                     //
    login log;                                          //Creating instance of login window
    conn con;                                           //Creating instance of connection window
    accountCreate acct;                                 //Creating instance of account creation window

public slots:
    void showLog(QString temphost, int tempport);       //Slot to be activated when you connect to the server, takes the host address and the port number from the login window
    void showMain(int userId);                          //Slot to be activated when you login, takes the userid from the login window
    void createAcc();                                   //Slot to be activated when you click the create account button on the login window
    void mainClosed();                                  //Slot to be activated when you are closing the program, closes and ends the main window

private slots:
    void on_Exit_Button_clicked();                      //Private slot that ends the program when the exit button is clicked, takes signal given off from button click
};

#endif // MAINWINDOW_H

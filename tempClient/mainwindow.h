#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "accountcreate.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString host;
    int port;
    int useId;

private:
    Ui::MainWindow *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    login log;
    conn con;
    accountCreate acct;

public slots:
    void showLog(QString temphost, int tempport);
    void showMain(int userId);
    void createAcc();
    //void accountcreated(QString created);
};

#endif // MAINWINDOW_H

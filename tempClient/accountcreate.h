#ifndef ACCOUNTCREATE_H
#define ACCOUNTCREATE_H

#include "login.h"

namespace Ui {
class accountCreate;
}

class accountCreate : public QMainWindow
{
    Q_OBJECT

public:
    explicit accountCreate(QWidget *parent = 0);
    accountCreate(QString host, int port);

    ~accountCreate();
    QString host;
    int port;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

signals:
    void gotoLog(QString akn);
    void usercreate(QString akn);


private:
    Ui::accountCreate *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    QTcpSocket *socket;


};

#endif // ACCOUNTCREATE_H

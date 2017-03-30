#ifndef LOGIN_H
#define LOGIN_H

#include "conn.h"

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();
    QString host;
    int port;

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void creatuser(QString aknowlege);


private:
    Ui::login *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    QTcpSocket *socket;

signals:
    void Want2CloseLog(int useId);
    void createAccount();
};

#endif // LOGIN_H

#ifndef LOGIN_H
#define LOGIN_H

#include "ui_login.h"
#include <QWidget>
#include <QtGui>
#include <QMouseEvent>
#include <QMainWindow>

namespace Ui {
class Login;

}
class Login : public QDialog
{
    Q_OBJECT


public:
    explicit Login(QWidget *parent = 0);
    virtual~Login();

private:
    Ui::Login *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;

signals:

public slots:
};

#endif // LOGIN_H

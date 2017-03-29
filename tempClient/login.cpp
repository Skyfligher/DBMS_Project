#include "login.h"
#include "ui_login.h"
#include <QMouseEvent>

Login::Login(QWidget *parent) :  QDialog(parent), ui(new Ui::Login)
{
    //ui = new Ui::login;
    ui->setupUi(this);
}

Login::~Login()
{
delete ui;
}

void Login::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void Login::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

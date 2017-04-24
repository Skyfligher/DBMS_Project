#ifndef CHANNELCREATE_H
#define CHANNELCREATE_H

#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class channelcreate;
}

class channelcreate : public QMainWindow
{
    Q_OBJECT

public:
    explicit channelcreate(QWidget *parent = 0);
    ~channelcreate();
    QString host;
    int port;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::channelcreate *ui;
    void mousePressEvent(QMouseEvent *event);       //For click and drag functionality on window
    void mouseMoveEvent(QMouseEvent *event);        //
    int m_nMouseClick_X_Coordinate;                 //
    int m_nMouseClick_Y_Coordinate;                 //
    QTcpSocket *socket;                             //Socket for talking to the server
};

#endif // CHANNELCREATE_H

#ifndef CONN_H
#define CONN_H


#include <QMainWindow>
#include <QMouseEvent>
#include <QMessageBox>
#include <QTcpSocket>

namespace Ui {
class conn;
}

class conn : public QMainWindow
{
    Q_OBJECT

public:
    explicit conn(QWidget *parent = 0);
    ~conn();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::conn *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    QTcpSocket *socket;

signals:
    void Want2Close(QString host, int port);
};

#endif // CONN_H

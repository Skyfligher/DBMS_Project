#ifndef CONNECTIONHANDLE_H
#define CONNECTIONHANDLE_H

#include <QObject>
#include <QTcpServer>
#include <QTextStream>
#include <QTcpSocket>


class connectionHandle : public QObject
{
    Q_OBJECT
public:
    explicit connectionHandle(QObject *parent = 0, int port = 1000);
    explicit connectionHandle(int port);
    QTcpServer *server;
    QTcpSocket *socket;

    QString handle();
signals:

public slots:
    void sessionOpen();
private:


};

#endif // CONNECTIONHANDLE_H

#include <QCoreApplication>
#include <QTextStream>
#include <QTcpSocket>
#include <QTcpServer>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <connectionhandle.h>


QTextStream cout(stdout);
QTextStream cin(stdin);
QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");    //adding database QTcpSocket *socket;
//QTcpServer *server;
int port;
bool test;

QString data;

QSqlQuery query;

QRegExp parse("[:;:]");

QString login(QString userMail, QString password);
void addUser(QString nickname, QString email, QString firstname, QString lastname, QString password);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
  /*  cout << "testing" << endl;
    cout.flush();
    port = cin.readLine().toInt();                                  //Where port will go
    cout << port << endl;
    cout.flush();
*/


    database.setHostName("127.0.0.1");                              //local host
    database.setPort(3306);
    database.setDatabaseName("main");                               //temp name for database
    database.setUserName("root");                                   //using root, should not in future
    database.setPassword("temp");                                   //password for the database
    bool dbConnect = database.open();                               //true if connected
    qDebug()<<database.open();

    if(dbConnect){                                            //Testing if database is connected
        cout << "I'm connected to the database!!" << endl;
        cout.flush();
    }
    else{
        cout << "I'm not connected!!!" << endl;
        cout.flush();
    }


        test = false;
        connectionHandle connect(1000);
    while(connect.server->isListening()){

        //connect.handle();
        QString userId;
        if(connect.server->waitForNewConnection(1000)){
        QString data = connect.handle();
        //QString temp = data;
        QStringList data2 = data.split(',');
        int command = data2.at(0).toInt();
        QString temp4 = data2.at(1);
        cout<<command<<endl;
        cout<<data<<endl;
        cout<<temp4;
        cout.flush();

    switch (command) {
    case 1:
        connect.socket->write("1");
        connect.socket->waitForBytesWritten(10);
        qDebug() << "confirmation sent!";
        connect.socket->abort();
        qDebug() << "socket aborted";
        test = false;
        break;
    case 2:
        qDebug()<< data.at(1);
        userId = login(data2.at(1),data2.at(2));
        qDebug() << userId;
        connect.socket->write(userId.toLatin1());
        connect.socket->waitForBytesWritten(10);
        qDebug() << "UserID sent!";
        connect.socket->abort();
        qDebug() << "socket aborted";
        test = false;
        break;
     case 3:

        connect.socket->write("1");
        connect.socket->waitForBytesWritten(10);
        connect.socket->abort();
        addUser(data2.at(1), data2.at(2), data2.at(3), data2.at(4), data2.at(5));
        test = false;
        break;
    }}
}

    return a.exec();
}











QString login(QString userMail, QString password)
{

    query.prepare("SELECT users.password FROM main.users WHERE users.email = '"+userMail+"'");
    query.exec();
    query.next();
    QString tempPass = query.value(0).toString();
    qDebug()<<query.lastError();

    query.prepare("SELECT users.id FROM main.users WHERE users.email = '"+userMail+"'");
    query.exec();
    query.next();
    QString userId = query.value(0).toString();
    qDebug()<<query.lastError();

    if(tempPass == password){
        return userId;
    }
    else{
        QString temp = "";
        return temp;
    }
}

void addUser(QString nickname, QString email, QString firstname, QString lastname, QString password)
{
    query.exec("SELECT MAX(id) FROM main.users");
    query.next();
    int maxuser = query.value(0).toInt();
    maxuser++;

    QDate joindate;
    joindate.currentDate();
    QString temp = joindate.currentDate().toString("dd.MM.yyyy");

    query.prepare("INSERT INTO main.users (id, nickname, email, "
                  "first, last, password, joindate) VALUES (?,?,?,?,?,?,?)");
    query.addBindValue(maxuser);
    query.addBindValue(nickname);
    query.addBindValue(email);
    query.addBindValue(firstname);
    query.addBindValue(lastname);
    query.addBindValue(password);
    query.addBindValue(temp);


    if(!query.exec()){
        qDebug() << query.lastError();
    }

    QString tablenumber = QString::number(maxuser);
    query.prepare("CREATE TABLE Person"+tablenumber+" (idchan VARCHAR(45),"
                                                    " datetime VARCHAR(45), message LONGTEXT, CONSTRAINT PK_Person"
                  +tablenumber+" PRIMARY KEY (idchan, datetime))");

    if(!query.exec()){
        qDebug() << query.lastError();
    }
}

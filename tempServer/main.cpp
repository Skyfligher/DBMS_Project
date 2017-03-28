#include <QCoreApplication>
#include <QTextStream>
#include <QTcpSocket>
#include <QTcpServer>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>


QTextStream cout(stdout);
QTextStream cin(stdin);
QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");    //adding database QTcpSocket *socket;
QTcpServer *server;
int port;

QString data;

QSqlQuery query;

bool logIn(QString userMail, QString password);
void addUser(QString nickname, QString email, QString firstname, QString lastname, QString password);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cout << "testing" << endl;
    cout.flush();
    port = cin.readLine().toInt();                                  //Where port will go
    cout << port << endl;
    cout.flush();



    database.setHostName("127.0.0.1");                              //local host
    database.setPort(3306);
    database.setDatabaseName("main");                               //temp name for database
    database.setUserName("root");                                   //using root, should not in future
    database.setPassword("temp");                                   //password for the database
    bool dbConnect = database.open();                               //true if connected
    qDebug()<<database.open();

    if(database.open()){                                            //Testing if database is connected
        cout << "I'm connected to the database!!" << endl;
        cout.flush();
    }
    else{
        cout << "I'm not connected!!!" << endl;
        cout.flush();
    }



    server = new QTcpServer();                                      //Setting up tcp server
    server ->listen(QHostAddress::Any,port);                        //Set to listen on port

    if(server->isListening()){                                      //Testing if listening on port
        cout << "I'm Listening!!!" << endl;
        cout.flush();
    }
    else{
        cout << "I can't hear anything!!!" << endl;
        cout.flush();
    }



    do{
        while(server->hasPendingConnections()){
            QTcpSocket *socket = server -> nextPendingConnection();
            QByteArray temp = socket->readAll();
            QString data = temp.data();

        }
    }
    while(!server->hasPendingConnections());





    cout << "give me a name" << endl;
    cout.flush();                                                   //Just testing if function works
    QString temp;                                                   //This will be replaced by a function to recieve
    temp = cin.readLine();                                          //incoming connections
    addUser("temp", temp, "temp", "temp", "temp");




    return a.exec();
}

bool logIn(QString userMail, QString password)
{
    query.exec("SELECT password FROM users WHERE email = "+userMail+" OR nickname = "+userMail);
    query.next();
    QString tempPass = query.value(0).toString();

    if(tempPass == password){
        return true;
    }
    else{
        return false;
    }
}

void addUser(QString nickname, QString email, QString firstname, QString lastname, QString password)
{
    query.exec("SELECT MAX(id) FROM users");
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
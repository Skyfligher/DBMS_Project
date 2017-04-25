#include <QCoreApplication>
#include <QTextStream>
#include <QTcpSocket>
#include <QTcpServer>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <connectionhandle.h>
#include <QThread>


QTextStream cout(stdout);
QTextStream cin(stdin);
QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");    //adding database QTcpSocket *socket;

int port;
bool test;
QString currentPeer;
QString data;
QString chat;
QStringList currentUsers;
QSqlQuery query;
//QRegExp parse("[:;:]");   will be used in the future, currently parsing with commas, not feasable in future. Cannot have commas in messages right now

QString login(QString userMail, QString password);
int addUser(QString nickname, QString email, QString firstname, QString lastname, QString password);
int addUserTable(QString nickname, QString password);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    /*  cout << "testing" << endl;
    cout.flush();
    port = cin.readLine().toInt();                                  //Where port will go, for future use in changing what port is used, dont worry about it for the project
    cout << port << endl;
    cout.flush();
*/


    database.setHostName("127.0.0.1");          //local host
    database.setPort(3306);                     //Setting port for the database, 3306 default
    database.setDatabaseName("main");           //temp name for database
    database.setUserName("root");               //using root, should not in future
    database.setPassword("temp");               //password for the database
    qDebug()<<database.open();                  //Outputs if database is open

    connectionHandle connect(1000);             //Tell the connectionHandle object connect to listen on port 1000
    while(connect.server->isListening())            //Main while loop for the server, constantly listens
    {
        QString userId;                                     //UserId for use in the various cases
        if(connect.server->waitForNewConnection(1000))      //Waiting for connection
        {
            QStringList data = connect.handle();        //.handle() interprets and parses the data, gives it back as a QStringList
            QString temp1 = connect.socket->peerAddress().toString();
            QStringList temps = temp1.split("::ffff:");
            currentPeer = temps.value(1);
            if(data.at(0) != "")                        //If there was an issue, no data, skips to debug output
            {
                int command = data.at(0).toInt();       //Checks what command is issued, the .at(0), will be an integer
                switch (command)
                {                                        //Passes the command number
                case 1:              //Ping, checking for connection
                {
                    connect.socket->write("1");                 //Sending acknowledgment
                    connect.socket->waitForBytesWritten(10);    //Waiting for data to be written
                    connect.socket->abort();                    //Closing the socket
                    break;
                }
                case 2:             //Login command
                {
                    qDebug()<<"2 Pressed";
                    QString temp1 = connect.socket->peerAddress().toString();
                    QStringList temps = temp1.split("::ffff:");
                    currentUsers<<temps.value(1);
                    userId = login(data.at(1),data.at(2));      //Passes email and password to the login function, login function passes back user id or issues that are taken care of by the client
                    connect.socket->write(userId.toUtf8());     //Writing data to the socket .toUtf8 changes QString to byte array
                    connect.socket->waitForBytesWritten(10);    //Waiting for data to be written
                    connect.socket->abort();
                    break;
                }
                case 3:             //Create Account
                {
                    int acknowlegement = addUser(data.at(1), data.at(2), data.at(3), data.at(4), data.at(5));   //Passes user info to addUser function, returns acknowlegement number
                    QString send = QString::number(acknowlegement);         //Sending acknowlegement number, tells client if done or had issues
                    connect.socket->write(send.toUtf8());                   //Converting QString to byte array and writing
                    connect.socket->waitForBytesWritten(10);                //Waiting for the information to be written
                    connect.socket->abort();                                //Closing the socket
                    break;
                }
                case 4:
                {
                    qDebug()<<"4 pressed";
                    query.prepare("SELECT userid,timedate,message FROM main.channel;");
                    if(query.exec())
                    {
                        int messages = query.size();

                        for(int t = 1; t <= messages; t++)
                        {
                            query.next();
                            chat.append("<"+query.value(0).toString()+" "+query.value(1).toString()+"> "+query.value(2).toString()+",");
                        }
                        connect.socket->write(chat.toUtf8());
                        connect.socket->waitForBytesWritten(100);
                        connect.socket->abort();
                        query.clear();
                        qDebug()<<"sent";
                        break;
                    }
                    else
                    {
                        break;
                    }

                }
                case 5:
                {
                    qDebug()<<"five hit";
                    QString temp2 = connect.socket->peerAddress().toString();
                    QStringList temps = temp2.split("::ffff:");
                    currentPeer = temps.value(1);
                    QDateTime temp = temp.currentDateTime();
                    QString table = "person"+data.at(1);
                    QString time = temp.toString("dd.MM.yyyy HH:mm:ss");
                    query.prepare("INSERT INTO main."+table+" (idchan, timedate, message) VALUES (?,?,?); INSERT INTO main.channel (userid, timedate, message) VALUES ('"+data.at(1)+"','"+time+"','"+data.at(2)+"');");

                    query.addBindValue("channel");
                    query.addBindValue(temp.toString("dd.MM.yyyy HH:mm:ss"));
                    query.addBindValue(data.at(2));

                    query.exec();
                    /*
                    if(query.exec())
                    {
                        qDebug()<<"query";
                        connect.socket->abort();
                        query.exec("SELECT users.nickname FROM main.users WHERE users.id = '"+data.at(1)+"';");
                        query.next();
                        QString tempMessage = "<"+query.value(0).toString()+" "+temp.toString("dd.MM.yyyy HH:mm:ss")+"> "+data.at(2);
                        qDebug()<<tempMessage;
                        qDebug()<<currentUsers.size();
                       for(int t = 0; t < currentUsers.size(); t++)
                        {   qDebug()<<currentUsers.at(t)<<currentPeer;
                            qDebug()<<"testing";

                            if(currentUsers.at(t) != currentPeer)
                            {
                                qDebug()<<currentUsers.at(t)<<currentPeer;
                            connect.socket->connectToHost(currentUsers.at(t),port);
                            if(connect.socket->state() == QAbstractSocket::ConnectedState)
                            {
                                connect.socket->write(tempMessage.toUtf8());
                                connect.socket->waitForBytesWritten(100);
                                connect.socket->abort();
                               // break;
                            }
                            }
                        }
                    }*/
                    connect.socket->abort();
                    break;
                }
                case 6:
                {
                    query.prepare("SELECT users.id FROM main.users WHERE users.nickname = '"+data.at(1)+"';");
                    if(query.exec())
                    {
                        query.next();
                        QString uid = query.value(0).toString();
                        query.prepare("SELECT * FROM main.person"+uid+";");
                        if(query.exec())
                        {
                            int messages = query.size();

                            for(int t = 1; t <= messages; t++)
                            {
                                query.next();
                                chat.append("<"+query.value(0).toString()+" "+query.value(1).toString()+"> "+query.value(2).toString()+",");
                            }
                            connect.socket->write(chat.toUtf8());
                            connect.socket->waitForBytesWritten(100);
                            connect.socket->abort();
                            query.clear();
                            break;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                case 7:
                {
                    qDebug()<<"7 was taken";
                    query.prepare("SELECT * FROM main.channel;");
                    if(query.exec())
                    {
                        int messages = query.size();
                        QString currentmsgs = data.value(1);
                        messages = messages - currentmsgs.toInt();
                        query.prepare("select * from main.channel order by timedate desc limit "+QString::number(messages)+";");
                        if(query.exec())
                        {
                            int querysize = query.size();
                        for(int t = 1; t <= querysize; t++)
                        {
                            query.next();
                            chat.append("<"+query.value(0).toString()+" "+query.value(1).toString()+"> "+query.value(2).toString()+",");
                        }
                        connect.socket->write(chat.toUtf8());
                        connect.socket->waitForBytesWritten(100);
                        connect.socket->abort();
                        query.clear();
                        break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                }

            }
            else
            {
                qDebug()<<"No Data Found";      //If empty data is recieved, continues the main loop and gives error to console
            }
        }
    }

    return a.exec();
}











QString login(QString userMail, QString password)       //Function to check database against login credentials
{

    query.prepare("SELECT users.password FROM main.users WHERE users.email = '"+userMail+"'");      //Preparing to query account password, based on the email given
    if(query.exec())                                                //If the query executes, true
    {
        query.next();                                               //Gets the current query results
        if(query.value(0).toString() != "")                         //Gets the first returned value, the password, checks if it is empty (empty if account does not exist)
        {
            QString tempPass = query.value(0).toString();           //Sets tempPass to the account password
            if(tempPass == password)                                //Checks password against known password
            {
                query.prepare("SELECT users.id FROM main.users WHERE users.email = '"+userMail+"'");    //Preparing to query the users id from the given email
                query.exec();                                       //Executes query
                query.next();                                       //Gets the current query results
                QString userId = query.value(0).toString();         //Sets userId
                return userId;                                      //Returns userId
            }
            else
            {
                QString temp = "failedPass";            //Passwords don't match
                return temp;                            //Returning failed status
            }
        }
        else
        {
            QString temp = "failedEmail";               //Emails don't match
            return temp;                                //Returning failed status
        }
    }
    else
    {
        QString temp = "databaseError";                 //Query did not go through
        return temp;                                    //Returning failed status
    }
}

int addUser(QString nickname, QString email, QString firstname, QString lastname, QString password)         //Adds user account
{
    query.exec("SELECT MAX(id) FROM main.users");                   //Gets the largest id number
    query.next();                                                   //Gets the current query results
    int maxuser = query.value(0).toInt();                           //Setting max userId
    maxuser++;                                                      //Iterates maxuser, new highest userId number
    QString tablename = "Person"+QString::number(maxuser);          //String for the users message table, Person(idnumber) ex: Person3
    QDate joindate;                                                 //String for the users join date
    joindate.currentDate();                                         //Gets the current date from the server machine, and sets joindate
    QString temp = joindate.currentDate().toString("dd.MM.yyyy");   //Changes joindate to new form for the database
    query.prepare("INSERT INTO main.users (id, nickname, email, first, last, "                              //Two querys being prepared in one statement
                  "password, joindate) VALUES (?,?,?,?,?,?,?); CREATE TABLE "                               //First is adding the users row into the users table
                  +tablename+" (idchan VARCHAR(45), timedate VARCHAR(45), message "                         //The second is creating the users message table
                             "LONGTEXT, CONSTRAINT PK_"+tablename+" PRIMARY KEY (idchan, timedate))");      //No Bind value is used for the table name, just concatinated

    query.addBindValue(maxuser);        //The bind values in the query are denoted by a ?
    query.addBindValue(nickname);       //each value is added sequencially
    query.addBindValue(email);          //
    query.addBindValue(firstname);      //
    query.addBindValue(lastname);       //
    query.addBindValue(password);       //
    query.addBindValue(temp);           //

    if(query.exec())                    //Checking if the query was exicuted
    {
        return 1;                       //Returns 1 if it was exicuted
    }
    else
    {
        qDebug()<<query.lastError();    //Gives error to console
        return 0;                       //Returns 0 for failed status
    }
}


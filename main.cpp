#include <QCoreApplication>
#include "mytcpserver.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyTcpServer* myserv = MyTcpServer::create_instance(); // server
    return a.exec();
}

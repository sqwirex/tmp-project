#include "client_object.h"
#include <functions_for_server.h>
#include <QList>
#include "client_object.h"
#include <QByteArray>

extern QList<client*> clients;
extern functions_for_server* servers_functions;

client::client(qintptr client_description): client_description(client_description)
{
   initialization();
   this->exec(); // запускаем обработку сообщений.
}

client::~client() {
   this->client_socket.close();
   this->quit(); // выключаем поток.

}

void client::initialization() {
   client_socket.setSocketDescriptor(client_description); // мы создали новый сокет и идентифицируем его дескриптором уже существующим
   clients.push_back(this);
   hello_message(); // отправляем в консоль приветственное сообщение. Статическая функция.
   connect(&client_socket, &QTcpSocket::readyRead, this, &client::slot_read_from_client); // читаем сообщения от клиента
   connect(&client_socket, &QTcpSocket::disconnected, this, &client::slot_close_connection); // если сокет отключается от сервера, вызываем функцию slot_close_connection
   this->run(); // запускаем поток.
}

void client::slot_read_from_client() {
   QString data;
   while (client_socket.bytesAvailable()) { // читаем сообщение от клиента
      data.push_back(client_socket.readAll());  // помещаем сообщение от клиента в data.
   }
   qDebug() << QString("%1 Client ").arg(servers_functions->get_server_time()) << &client_socket << QString(" send message: %1").arg(QString(data)).simplified();
   this->client_socket.write(data.toLatin1()); // ОТПРАВЛЯЕМ ОТПРАВЛЕННОЕ СООБЩЕНИЕ ОБРАТНО КЛИЕНТУ
}

void client::slot_close_connection() {
   clients.removeAll(this);
   bye_message();
   delete this;
}


// СЛУЖЕБНЫЕ ФУНКЦИИ ДЛЯ РАБОТЫ В РАМКАХ КЛАССА

void client::hello_message() {

   if (clients.size() == 1) {
      qDebug() << QString("%1 Client socket has connected. Сurrently 1 socket is connected").arg(servers_functions->get_server_time());
    }
    else if (clients.size() > 1) {
       qDebug() << QString("%1 Client socket has connected. Сurrently %2 sockets are connected").arg(servers_functions->get_server_time()).arg(QString::number(clients.size()));
    }
}

void client::bye_message() {
   if (clients.size() == 0)
      qDebug() << QString("%1 The client has disconnected. No clients at the moment").arg(servers_functions->get_server_time());
   else if (clients.size() == 1)
      qDebug() << QString("%1 The client has disconnected. Сurrently 1 socket is connected").arg(servers_functions->get_server_time());
   else if (clients.size() > 1)
      qDebug() << QString("%1 The client has disconnected. Сurrently %2 sockets are connected").arg(servers_functions->get_server_time()).arg(QString::number(clients.size()));
}

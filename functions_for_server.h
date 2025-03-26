#ifndef FUNCTIONS_FOR_SERVER_H
#define FUNCTIONS_FOR_SERVER_H
#include <QString>
#include <ctime>

class functions_for_server
{
private:
   functions_for_server();
   functions_for_server(const functions_for_server&);
   static functions_for_server* p_instance;
public:
   static functions_for_server* get_instance();
   QString get_server_time();
};

#endif // FUNCTIONS_FOR_SERVER_H

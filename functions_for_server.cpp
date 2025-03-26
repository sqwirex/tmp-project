#include "functions_for_server.h"


functions_for_server* functions_for_server::p_instance = nullptr;

functions_for_server::functions_for_server() {}

functions_for_server* functions_for_server::get_instance() {
   if (p_instance == nullptr) {
      p_instance = new functions_for_server();
   }
   return p_instance;
}


QString functions_for_server::get_server_time() {
   time_t now_time = time(nullptr); // получаем время на сервере в данный момент.
   tm* time_struct = localtime(&now_time); // конвертируем время в удобную структуру (год, месяц, число, день, час, минута, секунда, миллисекунда)
   char time_format[100];
   strftime(time_format, sizeof(time_format), "[%b %d %Y %H:%M:%S]", time_struct);
   return QString(time_format);
}

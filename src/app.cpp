#include "../inc/app.h"
#include "config/db_connection.h"

int main () {

  Logger::Init();
  DBConnection g_DB;
  httplib::Server g_Server;
  APP_TRACE("APP INITIALIZED");

  g_Server.Get("/life-check", [](const httplib::Request&, httplib::Response& res) {
    res.set_content("hello", "text/plain");
  });
  g_Server.listen("0.0.0.0", 8080);

  return 0;
}
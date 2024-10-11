#include "../inc/app.h"

int main () {
  crow::SimpleApp app;

  CROW_ROUTE(app, "/")
    ([]() {
        return "Hello world!";
    });
    app.bindaddr("127.0.0.1");
    app.port(8080).run();

  return 0;
}
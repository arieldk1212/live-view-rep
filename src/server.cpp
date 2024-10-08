#include "../inc/server.h"
#include "../lib/Crow/include/crow.h"


int main () {
  crow::SimpleApp app;

  CROW_ROUTE(app, "/")
  ([]() {
    return "hello";
  });

  app.run(8000).run();
}
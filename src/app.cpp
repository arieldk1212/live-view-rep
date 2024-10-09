#include "../inc/live_view.h"

int main () {
  crow::SimpleApp app;

  CROW_ROUTE(app, "/")
    ([]() {
        return "Hello world!";
    });

    app.port(8000).run();

  return 0;
}
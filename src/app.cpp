#include "../inc/app.h"
#include "config/logger.h"

int main () {
  LOG_DEBUG("Starting App..");
  SqlConnection m_sql;
  httplib::Server svr;
  
  svr.Get("/life-check", [](const httplib::Request&, httplib::Response& res) {
    res.set_content("hello", "text/plain");
  });
  LOG_INFO("TEST AT /life-check");
  svr.listen("0.0.0.0", 8080);

  return 0;
}

#include "../inc/app.h"

int main () {

  SqlConnection m_sql;
  httplib::Server svr;
  
  svr.Get("/life-check", [](const httplib::Request&, httplib::Response& res) {
    res.set_content("hello", "text/plain");
  });
  svr.listen("0.0.0.0", 8080);

  return 0;
}

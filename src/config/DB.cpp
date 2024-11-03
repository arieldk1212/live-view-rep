#include "../../inc/Config/DB.h"

namespace DB {

DBConnection::DBConnection() {
  m_ConnectionInfo.insert({"HOST", "localhost"});
  m_ConnectionInfo.insert({"PORT", "5432"});
  m_ConnectionInfo.insert({"DB", "arielkriheli"});
  m_ConnectionInfo.insert({"USER", "arielkriheli"});
  m_ConnectionInfo.insert({"PASSWORD", "password"});

  std::string connection_string = "user=" + \
    m_ConnectionInfo["USER"] + " password=" + m_ConnectionInfo["PASSWORD"] + \
    " host=" + m_ConnectionInfo["HOST"] + " port=" + m_ConnectionInfo["PORT"] + \
    " dbname=" + m_ConnectionInfo["DB"];
  m_ConnectionString = std::move(connection_string);

  m_DBConnection = std::make_shared<pqxx::connection>(m_ConnectionString);
  APP_INFO("DB INIT SUCCESS");
};

}
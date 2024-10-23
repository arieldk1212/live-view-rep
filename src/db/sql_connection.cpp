#include "../../inc/db/sql_connection.h"

SqlConnection::SqlConnection() {
  m_connection_info.insert({"HOST", "localhost"});
  m_connection_info.insert({"PORT", "5432"});
  m_connection_info.insert({"DB", "arielkriheli"});
  m_connection_info.insert({"USER", "arielkriheli"});
  m_connection_info.insert({"PASSWORD", "password"});

  const std::string connection_string = "user=" + \
    m_connection_info["USER"] + " password=" + m_connection_info["PASSWORD"] + \
    " host=" + m_connection_info["HOST"] + " port=" + m_connection_info["PORT"] + \
    " dbname=" + m_connection_info["DB"];
  m_connection_string = std::move(connection_string);

  m_sql_connection = std::make_unique<pqxx::connection>(m_connection_string);
};

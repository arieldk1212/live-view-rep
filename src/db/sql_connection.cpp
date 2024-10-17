#include "../../inc/db/sql_connection.h"

SqlConnection::SqlConnection() {

  m_connection_info.insert({"HOST", std::string{std::getenv("POSTGRES_HOST")}});
  m_connection_info.insert({"PORT", std::string{std::getenv("POSTGRES_PORT")}});
  m_connection_info.insert({"DB", std::string{std::getenv("POSTGRES_DB")}});
  m_connection_info.insert({"USER", std::string{std::getenv("POSTGRES_USER")}});
  m_connection_info.insert({"PASSWORD", std::string{std::getenv("POSTGRES_PASSWORD")}});

  // const std::string connection_string = "postgres://" + \
    m_connection_info["USER"] + ":" + m_connection_info["PASSWORD"] + \
    "@" + m_connection_info["HOST"] + ":" + m_connection_info["PORT"] + \
    "/" + m_connection_info["DB"];
  const std::string connection_string = "user=" + \
    m_connection_info["USER"] + " password=" + m_connection_info["PASSWORD"] + \
    " host=" + m_connection_info["HOST"] + " port=" + m_connection_info["PORT"] + \
    " dbname=" + m_connection_info["DB"];
  std::cout << connection_string;
  m_connection_string = std::move(connection_string);

  m_sql_connection = std::make_unique<pqxx::connection>(m_connection_string);
}
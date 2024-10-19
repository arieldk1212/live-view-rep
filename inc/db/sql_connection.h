#ifndef SQL_CONNECTION_H
#define SQL_CONNECTION_H

#include <memory>
#include <pqxx/pqxx>

typedef std::map<std::string, std::string> t_conn_info;
typedef std::unique_ptr<pqxx::connection> t_conn_ptr;

class SqlConnection {
public:
  SqlConnection();

private:
  t_conn_ptr m_sql_connection;
  t_conn_info m_connection_info;
  std::string m_connection_string;
};

#endif
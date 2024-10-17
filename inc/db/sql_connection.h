#ifndef SQL_CONNECTION_H
#define SQL_CONNECTION_H

#include <algorithm>
#include <memory>
#include <cstdlib>
#include <pqxx/pqxx>
#include <libenvpp/env.hpp>
#include <iostream>

typedef std::map<std::string, std::string> ConnInfo;
typedef std::unique_ptr<pqxx::connection> ConnPtr;

class SqlConnection {
public:
  SqlConnection();

private:
  // ConnPtr m_sql_connection;
  ConnInfo m_connection_info;
  std::string m_connection_string;
};

#endif
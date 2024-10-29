#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <memory>
#include <pqxx/pqxx>

#include "config/logger.h"

typedef std::map<std::string, std::string> t_ConnInfo;
typedef std::unique_ptr<pqxx::connection> t_ConnPtr;

class DBConnection {
public:
  DBConnection();

private:
  t_ConnPtr m_DBConnection;
  t_ConnInfo m_ConnectionInfo;
  std::string m_ConnectionString;
};

#endif
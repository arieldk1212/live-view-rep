#ifndef DB_H
#define DB_H

#include <pqxx/pqxx>

class DBConnection {
public:
  explicit DBConnection(const std::string &ConnectionString);
  ~DBConnection() = default;

  DBConnection(DBConnection &&) = delete;
  DBConnection(const DBConnection &other) = delete;
  DBConnection &operator=(DBConnection &&) = delete;
  DBConnection &operator=(const DBConnection &other) = delete;

private:
  pqxx::connection m_DBConnection;
  pqxx::work m_DBWorker{m_DBConnection};
};

#endif
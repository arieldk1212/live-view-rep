#ifndef DATABASE_H
#define DATABASE_H

#include <pqxx/pqxx>
#include <string_view>

/*
* This header file shouldn't be used directly!
*/

class DatabaseConnection {
public:
  explicit DatabaseConnection(const std::string &ConnectionString);
  ~DatabaseConnection();

  bool IsDatabaseConnected();

  pqxx::result Query(const std::string &Query);
  void Commit();

private:
  pqxx::connection m_DatabaseConnection;
  pqxx::work m_DatabaseWorker{m_DatabaseConnection};
};

#endif
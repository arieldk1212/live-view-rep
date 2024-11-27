#ifndef DATABASE_H
#define DATABASE_H

#include <pqxx/pqxx>

/*
* This header file shouldn't be used directly!
*/

class DatabaseConnection {
public:
  explicit DatabaseConnection(const std::string &ConnectionString);
  ~DatabaseConnection();

  bool IsDatabaseConnected();

  void Commit(); // INFO: makes sure every change is stated.
  pqxx::result Query(const std::string &Query); // INFO: query, like GET.
  void Execute(const std::string &Query); // INFO: execute queries.

private:
  pqxx::connection m_DatabaseConnection;
  pqxx::work m_DatabaseWorker{m_DatabaseConnection};
};

#endif
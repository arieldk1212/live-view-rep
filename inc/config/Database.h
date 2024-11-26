#ifndef DATABASE_H
#define DATABASE_H

#include <pqxx/pqxx>

class DatabaseConnection {
public:
  explicit DatabaseConnection(const std::string &ConnectionString);
  ~DatabaseConnection() = default;

  void Commit();
  pqxx::result Query(const std::string &Query);
  void Execute(const std::string &Query);

  // TODO: create more Database related Methods ofr tables and more.

private:
  bool m_IsConnected;
  pqxx::connection m_DatabaseConnection;
  pqxx::work m_DatabaseWorker{m_DatabaseConnection};
};

#endif
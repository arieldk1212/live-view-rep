#ifndef DATABASE_H
#define DATABASE_H

#include <pqxx/pqxx>

/*
 * This header file shouldn't be used directly!
 */

class DatabaseManager;

class DatabaseConnection {
public:
  explicit DatabaseConnection(const std::string &ConnectionString);
  ~DatabaseConnection();

  bool IsDatabaseConnected();

private:
  pqxx::connection m_DatabaseConnection;
  pqxx::work m_DatabaseWorker{m_DatabaseConnection};

private:
  pqxx::result Query(const std::string &Query);
  void Commit();

private:
  friend class DatabaseManager;
};

#endif
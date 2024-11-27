#include "../../inc/Config/Database.h"

DatabaseConnection::DatabaseConnection(const std::string &ConnectionString)
    : m_DatabaseConnection(ConnectionString) {}

DatabaseConnection::~DatabaseConnection() { m_DatabaseConnection.close(); }

bool DatabaseConnection::IsDatabaseConnected() {
  return m_DatabaseConnection.is_open();
}

void DatabaseConnection::Commit() {
  if (IsDatabaseConnected()) {
    m_DatabaseWorker.commit();
  }
}

pqxx::result DatabaseConnection::Query(const std::string &Query) {
  pqxx::result result;
  if (!IsDatabaseConnected()) {
    return std::move(result);
  }
  result = m_DatabaseWorker.exec(Query);
  return std::move(result);
}

void DatabaseConnection::Execute(const std::string &query) {
  if (IsDatabaseConnected()) {
    m_DatabaseWorker.exec(query);
  }
}
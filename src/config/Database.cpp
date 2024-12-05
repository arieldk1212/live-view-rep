#include "../../inc/Config/Database.h"

DatabaseConnection::DatabaseConnection(const std::string &ConnectionString)
    : m_DatabaseConnection{ConnectionString} {}

DatabaseConnection::~DatabaseConnection() { m_DatabaseConnection.close(); }

bool DatabaseConnection::IsDatabaseConnected() {
  return m_DatabaseConnection.is_open();
}

pqxx::result DatabaseConnection::Query(const std::string &Query) {
  if (IsDatabaseConnected()) {
    return m_DatabaseWorker.exec(Query);
  }
  return {};
}

void DatabaseConnection::Commit() {
  if (IsDatabaseConnected()) {
    m_DatabaseWorker.commit();
  }
}
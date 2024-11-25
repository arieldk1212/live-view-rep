#include "../../inc/Config/Database.h"

DatabaseConnection::DatabaseConnection(const std::string &ConnectionString)
    : m_DatabaseConnection(ConnectionString), m_IsConnected(true) {}

void DatabaseConnection::Commit() { m_DatabaseWorker.commit(); }

pqxx::result DatabaseConnection::Query(const std::string &Query) {
  return m_DatabaseWorker.exec(Query);
}

void DatabaseConnection::Execute(const std::string &Query) {
  if (m_IsConnected) {
    m_DatabaseWorker.exec(Query);
  }
}
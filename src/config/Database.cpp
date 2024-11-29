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
  if (IsDatabaseConnected()) {
    result = m_DatabaseWorker.exec(Query);
    return std::move(result);
  }
  return result;
}

std::string_view DatabaseConnection::Execute(const std::string_view &Command) {
  if (IsDatabaseConnected()) {
    m_DatabaseWorker.exec(Command);
  }
}
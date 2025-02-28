#include "../../inc/Config/DatabasePool.h"

DatabasePool::DatabasePool(int PoolSize, std::string &&DatabaseConnectionString)
    : m_DatabasePoolSize(PoolSize),
      m_DatabaseString(std::move(DatabaseConnectionString)) {
  if (m_DatabaseString.empty()) {
    APP_CRITICAL("DATABASE MANAGER ERROR - EMPTY CONNECTION STRING");
    throw std::invalid_argument("Database Connection String Empty.");
  }
  try {
    for (int i = 0; i < PoolSize; i++) {
      m_DatabasePool.emplace_back(
          std::make_shared<DatabaseManager>(m_DatabaseString));
    }
  } catch (const std::exception &e) {
    APP_ERROR("DATABASE POOL CONSTRUCTOR ERROR - " + std::string(e.what()));
  }
  APP_INFO("DATABASE POOL CREATED - NUMBER OF CONNECTIONS: " +
           std::to_string(PoolSize));
}

DatabasePool::~DatabasePool() {
  /** @todo add condition variable, if not all resets, wait. */
  Shutdown();
  APP_CRITICAL("DATABASE POOL DESTROYED");
}

void DatabasePool::Shutdown() {
  try {
    for (SharedManager &Connection : m_DatabasePool) {
      Connection.reset();
    }
    m_DatabasePool.clear();
  } catch (const std::exception &e) {
    APP_ERROR("DATABASE POOL SHUTDOWN ERROR - " + std::string(e.what()));
  }
}

DatabasePool::SharedManager &DatabasePool::GetConnection() {
  for (SharedManager &Connection : m_DatabasePool) {
    if (!Connection->IsDatabaseConnected()) {
      return Connection;
    }
  }
}
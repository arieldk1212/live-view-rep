#include "../../inc/Config/DatabasePool.h"

DatabasePool::DatabasePool(int PoolSize,
                           std::string &&DatabaseConnectionString) noexcept
    : m_DatabasePoolSize(PoolSize),
      m_DatabaseConnectionString(std::move(DatabaseConnectionString)) {
  for (int i = 0; i < PoolSize; i++) {
    m_DatabasePool.emplace_back(
        std::make_shared<DatabaseManager>(m_DatabaseConnectionString));
  }
  APP_INFO("DATABASE POOL CREATED - NUMBER OF CONNECTIONS: " +
           std::to_string(PoolSize));
}

DatabasePool::~DatabasePool() {
  /**
   * @todo add condition variable, if not all resets, wait.
   */
  for (auto &Connection : m_DatabasePool) {
    Connection.reset();
  }
  m_DatabasePool.clear();
  APP_CRITICAL("DATABASE POOL DESTROYED");
}
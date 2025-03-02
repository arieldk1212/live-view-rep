#include "../../inc/Config/DatabasePool.h"

DatabasePool::DatabasePool(std::string &&DatabaseConnectionString)
    : m_DatabaseString(std::move(DatabaseConnectionString)) {
  if (m_DatabaseString.empty()) {
    APP_CRITICAL("DATABASE MANAGER ERROR - EMPTY CONNECTION STRING");
    throw std::invalid_argument("Database Connection String Empty.");
  }
  try {
    std::lock_guard<std::mutex> lock(m_PoolMutex);
    for (int i = 0; i < m_DatabasePoolSize; i++) {
      m_DatabasePool.emplace(
          std::make_shared<DatabaseManager>(m_DatabaseString));
    }
  } catch (const std::exception &e) {
    APP_ERROR("DATABASE POOL CONSTRUCTOR ERROR - " + std::string(e.what()));
  }
  APP_INFO("DATABASE POOL CREATED - NUMBER OF CONNECTIONS: " +
           std::to_string(m_DatabasePoolSize));
}

DatabasePool::~DatabasePool() { APP_CRITICAL("DATABASE POOL DESTROYED"); }

DatabasePool::SharedManager DatabasePool::GetConnection() {
  std::unique_lock<std::mutex> lock(m_PoolMutex);
  m_PoolConditionVariable.wait(lock,
                               [this]() { return !m_DatabasePool.empty(); });
  auto Connection = std::move(m_DatabasePool.front());
  m_DatabasePool.pop();
  return Connection;
}

void DatabasePool::ReturnConnection(SharedManager &Connection) {
  {
    std::scoped_lock<std::mutex> lock(m_PoolMutex);
    m_DatabasePool.push(std::move(Connection));
  }
  m_PoolConditionVariable.notify_one();
}

std::string DatabasePool::ConnectionsReport() {
  int count = 0;
  std::string Status;
  auto Queue = m_DatabasePool;
  while (!Queue.empty()) {
    const auto &Connection = Queue.front();
    Status.append("Connection ")
        .append(std::to_string(++count))
        .append(": Ref Count: ")
        .append(std::to_string(Connection.use_count()))
        .append(", Connection: ")
        .append(std::to_string(Connection->IsDatabaseConnected()))
        .append("\n");
    Queue.pop();
  }
  std::cout << Status << "\n";
  return Status;
}

std::string DatabasePool::SingularConsumption(SharedManager &Connection) {
  std::cout << "Connection's Ref Count: "
            << std::to_string(Connection.use_count()) << "\n";
  return "Connection's Ref Count: " + std::to_string(Connection.use_count());
}
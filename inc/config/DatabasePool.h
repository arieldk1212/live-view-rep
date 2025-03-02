#ifndef DATABASEPOOL_H
#define DATABASEPOOL_H

#include "DatabaseManager.h"

#include <condition_variable>
#include <queue>

/**
 * @class DatabasePool
 * @todo add logging into database here, each connection will log its status
 * about himself, implement cache, optimize queries per given time, and monitor!
 */

class DatabasePool {
public:
  template <typename T> using Shared = std::shared_ptr<T>;
  using SharedManager = Shared<DatabaseManager>;

public:
  DatabasePool(std::string &&DatabaseConnectionString);
  ~DatabasePool();

  SharedManager GetConnection();
  void ReturnConnection(SharedManager &Connection);

  inline int GetPoolLimit() const { return m_DatabasePoolSize; }
  inline const std::string &GetConnectionString() const {
    return m_DatabaseString;
  }

  std::string ConnectionsReport();
  std::string SingularConsumption(SharedManager &Connection);

private:
  std::mutex m_PoolMutex;
  std::condition_variable m_PoolConditionVariable;

private:
  const int m_DatabasePoolSize{10};
  std::string m_DatabaseString;
  std::queue<SharedManager> m_DatabasePool;
};

#endif
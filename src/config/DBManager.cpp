#include "../../inc/Config/DBManager.h"

DBManager::DBManager() {
  std::string ConnectionString = "user=arielkriheli password=password "
                                 "host=localhost port=5432 dbname=arielkriheli";
  m_DBConnectionString = std::move(ConnectionString);
  m_DB = std::make_shared<DBConnection>(m_DBConnectionString);
}
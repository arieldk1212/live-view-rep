#include "../../inc/Models/LogModel.h"

LogModel::LogModel(std::shared_ptr<DatabaseManager> &Manager)
    : m_DatabaseManager(std::move(Manager)) {
  APP_INFO("LOGGER MODEL CREATED");
}

LogModel::~LogModel() {
  m_DatabaseManager.reset();
  APP_INFO("LOGGER MODEL DESTYOYED");
}

pqxx::result LogModel::Init(const StringUnMap &Fields) {
  return m_DatabaseManager->AddModel("Logger", Fields);
}
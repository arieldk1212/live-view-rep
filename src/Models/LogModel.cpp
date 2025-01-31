#include "../../inc/Models/LogModel.h"

LogModel::LogModel(std::shared_ptr<DatabaseManager> &Manager)
    : m_DatabaseManager(std::move(Manager)), m_TableName("Log") {
  APP_INFO("LOGGER MODEL RESOURCE CREATED");
}

LogModel::~LogModel() {
  m_DatabaseManager.reset();
  APP_INFO("LOGGER MODEL RESOURCE DESTYOYED");
}

pqxx::result LogModel::Init() {
  APP_INFO("LOG TABLE CREATED VIA ADDRESS MODEL");
  return m_DatabaseManager->AddModel("Log", m_LogFields);
}
#include "../../inc/Models/AddressModel.h"

AddressModel::AddressModel(std::shared_ptr<DatabaseManager> &Manager)
    : m_DatabaseManager(Manager), m_TableName("Address") {
  APP_INFO("ADDRESS MODEL RESOURCE CREATED");
}

AddressModel::~AddressModel() {
  m_DatabaseManager.reset();
  APP_CRITICAL("ADDRESS MODEL RESOURCE DESTROYED");
}

pqxx::result AddressModel::Init() {
  APP_INFO("ADDRESS TABLE CREATED VIA ADDRESS MODEL");
  return m_DatabaseManager->AddModel(m_TableName, m_AddressFields);
}

pqxx::result AddressModel::Add(const StringUnMap &Fields) {
  auto Result = m_DatabaseManager->InsertInto(m_TableName, Fields);
  return Result;
}
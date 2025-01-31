#include "../../inc/Models/AddressModel.h"

AddressModel::AddressModel(std::shared_ptr<DatabaseManager> &Manager)
    : m_DatabaseManager(std::move(Manager)) {
  APP_INFO("ADDRESS MODEL CREATED");
}

AddressModel::~AddressModel() {
  m_DatabaseManager.reset();
  APP_INFO("ADDRESS MODEL DESTYOYED");
}

pqxx::result AddressModel::Init(const StringUnMap &Fields) {
  return m_DatabaseManager->AddModel("Address", Fields);
}
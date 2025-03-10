#include "../../inc/Models/AddressModel.h"

AddressModel::AddressModel() : m_TableName("Address") {
  APP_INFO("ADDRESS MODEL RESOURCE CREATED");
}

AddressModel::~AddressModel() {
  APP_CRITICAL("ADDRESS MODEL RESOURCE DESTROYED");
}

pqxx::result AddressModel::Add(SharedManager &Manager, StringUnMap Fields) {
  Fields.emplace("addressdata", "{test1, test2}");

  return Manager->InsertInto(m_TableName, Fields);
}

Address AddressModel::GetAddressData(SharedManager &Manager, std::string ID) {
  return Address(Manager, std::move(ID));
}
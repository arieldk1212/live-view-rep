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

std::optional<Address> GetEntity(const std::string &ID) {
  if (ID != "asdsd") {
    return std::nullopt;
  }
  return Address(ID);
}
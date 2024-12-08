#include "../../inc/Models/DatabaseModel.h"
#include <string_view>

DatabaseModel::DatabaseModel(const std::string &ModelName,
                             const StringMap &ModelFields)
    : m_DatabaseModelName{ModelName}, m_DatabaseModelFields{ModelFields} {}

std::string DatabaseModel::GetModelName() const { return m_DatabaseModelName; }

std::string DatabaseModel::ModelFieldsSerialization() {
  std::string Response = "";
  for (auto &[key, value] : m_DatabaseModelFields) {
    Response += "Type: " + key + " Value: " + m_DatabaseModelFields[key];
  }
  return std::move(Response);
}

std::string DatabaseModel::ModelSerialization() {
  std::string Response;
  Response = "Model Name: " + m_DatabaseModelName + "\n";
  Response += "Model Fields: " + std::move(ModelFieldsSerialization()) + ".\n";
  return std::move(Response);
}

void DatabaseModel::ClearFields() { m_DatabaseModelFields.clear(); }

void DatabaseModel::InsertField(const std::string &FieldType,
                                const std::string &FieldValue) {
  m_DatabaseModelFields.insert(FieldType, FieldValue);
}

void DatabaseModel::ClearAndInsertFields(const StringMap &ModelFields) {
  ClearFields();
  m_DatabaseModelFields.insert(ModelFields.begin(), ModelFields.end());
}
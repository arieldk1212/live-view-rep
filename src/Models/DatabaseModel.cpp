#include "../../inc/Models/DatabaseModel.h"

DatabaseModel::DatabaseModel(const std::string &ModelName,
                             const StringMap &ModelFields)
    : m_DatabaseModelName{ModelName}, m_DatabaseModelFields{ModelFields} {}

const std::string DatabaseModel::GetModelName() const {
  return m_DatabaseModelName;
}

std::string DatabaseModel::ModelSerialization() {
  std::string Response;
  Response = "Model Name: " + m_DatabaseModelName + " ";
  Response += "Fields: ";
  for (auto &[key, value] : m_DatabaseModelFields) {
    Response += key + " - " + m_DatabaseModelFields[key] + " ";
  }
  return std::move(Response);
}

std::string ToLower(std::string &&String) {
  std::string Response = std::move(String);
  std::transform(Response.begin(), Response.end(), Response.begin(), ::tolower);
  return std::move(Response);
}

std::string DatabaseModel::QuerySerialization() { std::string Response; }

void DatabaseModel::ClearFields() { m_DatabaseModelFields.clear(); }

void DatabaseModel::InsertField(const std::string &FieldName,
                                const std::string &FieldType) {
  m_DatabaseModelFields.emplace(FieldName, FieldType);
}

void DatabaseModel::ClearAndInsertFields(const StringMap &ModelFields) {
  ClearFields();
  m_DatabaseModelFields.insert(ModelFields.begin(), ModelFields.end());
}
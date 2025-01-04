#include "../../inc/Models/DatabaseModel.h"

DatabaseModel::DatabaseModel(const std::string &ModelName,
                             const StringUnMap &ModelFields)
    : m_DatabaseModelName{ModelName}, m_DatabaseModelFields{ModelFields} {}

const std::string &DatabaseModel::GetModelName() const {
  return m_DatabaseModelName;
}

std::string DatabaseModel::ModelSerialization() const {
  std::string Response;
  Response.append("Model Name: ")
      .append(m_DatabaseModelName)
      .append(" ")
      .append("Fields: ");
  for (auto &[key, value] : m_DatabaseModelFields) {
    Response.append(key).append(" - ").append(value).append(" ");
  }
  if (!m_DatabaseModelFields.empty()) {
    Response.pop_back();
  }
  return Response;
}

void DatabaseModel::ClearFields() { m_DatabaseModelFields.clear(); }

void DatabaseModel::InsertField(const std::string &FieldName,
                                const std::string &FieldType) {
  try {
    m_DatabaseModelFields.emplace(FieldName, FieldType);
  } catch (const std::exception &e) {
    APP_ERROR("CANNOT HAVE 2 KEYS OF THE SAME VALUE - " + FieldName " - " +
              std::string(e.what()));
  }
}

void DatabaseModel::ChangeFieldName(const std::string &FieldName,
                                    const std::string &NewFieldName) {
  try {
    auto FieldKey = m_DatabaseModelFields.extract(FieldName);
    FieldKey.key() = NewFieldName;
    m_DatabaseModelFields.insert(std::move(FieldKey));
  } catch (const std::exception &e) {
    APP_ERROR("KEY NOT FOUND - " + FieldName + " - " + std::string(e.what()));
  }
}

void DatabaseModel::ChangeFieldType(const std::string &FieldName,
                                    const std::string &NewFieldType) {
  try {
    m_DatabaseModelFields[FieldName] = NewFieldType;
  } catch (const std::exception &e) {
    APP_ERROR("KEY NOT FOUND - " + FieldName + " - " + std::string(e.what()));
  }
}

void DatabaseModel::RemoveField(const std::string &FieldName) {
  try {
    m_DatabaseModelFields.erase(FieldName);
  } catch (const std::exception &e) {
    APP_ERROR("KEY NOT FOUND - " + FieldName + " - " + std::string(e.what()));
  }
}

// void DatabaseModel::ClearAndInsertFields(const StringUnMap &ModelFields) {
//   ClearFields();
//   m_DatabaseModelFields.insert(ModelFields.begin(), ModelFields.end());
// }
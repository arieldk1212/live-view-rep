#include "../../inc/Config/DatabaseManager.h"
#include "Config/DatabaseCommands.h"
#include "Models/DatabaseModel.h"

DatabaseManager::DatabaseManager(const std::string &DatabaseConnectionString)
    : m_DatabaseConnectionString(DatabaseConnectionString) {
  m_DatabaseManager =
      std::make_shared<DatabaseConnection>(m_DatabaseConnectionString);
}

DatabaseManager::~DatabaseManager() { m_DatabaseModels.clear(); }

bool DatabaseManager::DatabaseConnectionValidation() {
  return m_DatabaseManager->IsDatabaseConnected();
}

std::string
DatabaseManager::QuerySerialization(const StringUnMap &ModelFields) {
  std::string Response;
  for (const auto &[key, value] : ModelFields) {
    Response.append(key).append(" ").append(value).append(", ");
  }
  if (!ModelFields.empty()) {
    Response.pop_back();
    Response.pop_back();
  }
  return Response;
}

std::shared_ptr<DatabaseModel> &
DatabaseManager::operator[](const std::string &ModelName) {
  for (auto &Model : m_DatabaseModels) {
    if (Model && Model->GetModelName() == ModelName) {
      return Model;
    }
  }
  throw std::out_of_range("Model not found: " + ModelName);
}

std::shared_ptr<DatabaseModel>
DatabaseManager::GetModel(const std::string &ModelName) {
  return (*this)[ModelName];
}

pqxx::result DatabaseManager::AddModel(const std::string &ModelName,
                                       const StringUnMap &ModelFields) {
  m_DatabaseModels.emplace_back(
      std::make_shared<DatabaseModel>(ModelName, ModelFields));
  auto Response = CreateTable(ModelName, ModelFields);
  return Response;
}

pqxx::result DatabaseManager::AddColumn(const std::string &ModelName,
                                        const std::string &FieldName,
                                        const std::string &FieldType) {
  GetModel(ModelName)->InsertField(FieldName, FieldType);
  std::string query;
  query.append(DatabaseCommandToString(DatabaseQueryCommands::AlterTable))
      .append(ModelName)
      .append(" add ")
      .append(FieldName)
      .append(" ")
      .append(FieldType)
      .append(";");
  return MCrQuery(ModelName, query);
}

pqxx::result DatabaseManager::DropColumn(const std::string &ModelName,
                                         const std::string &FieldName) {
  GetModel(ModelName)->RemoveField(FieldName);
  std::string query;
  query.append(DatabaseCommandToString(DatabaseQueryCommands::AlterTable))
      .append(ModelName)
      .append(" ")
      .append(DatabaseCommandToString(DatabaseQueryCommands::UpdateDropColumn))
      .append(FieldName);
  return MCrQuery(ModelName, query);
}

pqxx::result DatabaseManager::AlterColumn(const std::string &ModelName,
                                          const std::string &FieldName,
                                          const std::string &NewFieldType) {
  GetModel(ModelName)->ChangeFieldType(FieldName, NewFieldType);
  std::string query;
  query.append(DatabaseCommandToString(DatabaseQueryCommands::AlterTable))
      .append(ModelName)
      .append(" ")
      .append(DatabaseCommandToString(DatabaseQueryCommands::AlterColumn))
      .append(FieldName)
      .append(" type ")
      .append(NewFieldType);
  return MCrQuery(ModelName, query);
}

// pqxx::result DatabaseManager::SwapAllColumns(const std::string &ModelName,
//                                              const StringUnMap &ModelFields)
//                                              {
//   GetModel(ModelName)->ClearAndInsertFields(ModelFields);
// }

pqxx::result DatabaseManager::InsertInto(const std::string &ModelName,
                                         const StringUnMap &Fields) {
  std::string query;
  std::string keys;
  std::string values;
  for (const auto &[key, value] : Fields) {
    keys.append(key).append(", ");
    values.append("'").append(value).append("', ");
  }
  if (!Fields.empty()) {
    keys.pop_back();
    keys.pop_back();
    values.pop_back();
    values.pop_back();
  }
  query.append(DatabaseCommandToString(DatabaseQueryCommands::InsertInto))
      .append(ModelName)
      .append(" (")
      .append(keys)
      .append(") values (")
      .append(values)
      .append(");");

  return MCrQuery(ModelName, query);
}

pqxx::result DatabaseManager::UpdateColumn(const std::string &ModelName,
                                           const std::string &FieldName,
                                           const std::string &NewFieldValue,
                                           const std::string &Condition) {
  std::string query;
  query.append(DatabaseCommandToString(DatabaseQueryCommands::Update))
      .append(ModelName)
      .append(" set ")
      .append(FieldName)
      .append(" = '")
      .append(NewFieldValue)
      .append("' where ")
      .append(Condition)
      .append(";");
  return MCrQuery(ModelName, query);
}

pqxx::result DatabaseManager::UpdateColumns(const std::string &ModelName,
                                            const StringUnMap &Fields,
                                            const std::string &Condition) {
  std::string query;
  query.append(DatabaseCommandToString(DatabaseQueryCommands::Update))
      .append(ModelName)
      .append(" set ");
  for (const auto &[key, value] : Fields) {
    query.append(key).append(" = '").append(value).append("', ");
  }
  query.pop_back();
  query.pop_back();
  query += " where " + Condition + ";";
  return MCrQuery(ModelName, query);
}

pqxx::result DatabaseManager::RemoveModel(const std::string &ModelName) {
  auto it =
      std::find_if(m_DatabaseModels.begin(), m_DatabaseModels.end(),
                   [&ModelName](const std::shared_ptr<DatabaseModel> &Model) {
                     return Model->GetModelName() == ModelName;
                   });
  if (it != m_DatabaseModels.end()) {
    m_DatabaseModels.erase(it);
    return DeleteTable(ModelName, DatabaseQueryCommands::DropDrop);
  }
  throw std::out_of_range("Model not found: " + ModelName);
}

pqxx::result DatabaseManager::TruncateModel(const std::string &ModelName) {
  GetModel(ModelName)->ClearFields();
  return DeleteTable(ModelName, DatabaseQueryCommands::DropTruncate);
}

pqxx::result DatabaseManager::GetModelData(const std::string &ModelName) {
  return GetTableData(ModelName);
}

pqxx::result DatabaseManager::GetModelData(const std::string &ModelName,
                                           const std::string &FieldName,
                                           const std::string &FieldValue) {
  return GetTableData(ModelName, FieldName, FieldValue);
}

std::string
DatabaseManager::GetSerializedModelData(const std::string &ModelName) {
  return GetSerializedTableData(ModelName);
}

// pqxx::result DatabaseManager::MUQuery(const std::string &TableName,
//                                     const std::string &query) {
//   try {
//     auto Response = m_DatabaseManager->UQuery(query);
//     APP_INFO("UQUERRY COMMITTED AT - " + TableName);
//     return Response;
//   } catch (pqxx::sql_error const &e) {
//     APP_ERROR("UQUERY ERROR AT TABLE - " + TableName + " " +
//               std::string(e.what()));
//     return {};
//   } catch (std::exception const &e) {
//     APP_ERROR("UQUERY GENERAL ERROR - " + std::string(e.what()));
//     return {};
//   }
// }

pqxx::result DatabaseManager::MCrQuery(const std::string &TableName,
                                       const std::string &query) {
  try {
    auto Response = m_DatabaseManager->CrQuery(query);
    APP_INFO("CRQUERRY COMMITTED AT - " + TableName);
    return Response;
  } catch (pqxx::sql_error const &e) {
    APP_ERROR("CRQUERY ERROR AT TABLE - " + TableName + " " +
              std::string(e.what()));
    return {};
  } catch (std::exception const &e) {
    APP_ERROR("CRQUERY GENERAL ERROR - " + std::string(e.what()));
    return {};
  }
}

pqxx::result DatabaseManager::CreateTable(const std::string &TableName,
                                          const StringUnMap &TableFields) {
  std::string query;
  query
      .append(DatabaseCommandToString(
          DatabaseQueryCommands::CreateTableIfNotExists))
      .append(TableName)
      .append("(")
      .append(QuerySerialization(TableFields))
      .append(");");
  return MCrQuery(TableName, query);
};

pqxx::result DatabaseManager::GetTableData(const std::string &TableName) {
  std::string query;
  query.append(DatabaseCommandToString(DatabaseQueryCommands::SelectAll))
      .append(TableName);
  return MCrQuery(TableName, query);
}

pqxx::result DatabaseManager::GetTableData(const std::string &TableName,
                                           const std::string &TableFieldName,
                                           const std::string &TableFieldValue) {
  std::string query;
  query.append(DatabaseCommandToString(DatabaseQueryCommands::SelectAll))
      .append(TableName)
      .append(" where ")
      .append(TableFieldName)
      .append("=")
      .append("'")
      .append(TableFieldValue)
      .append("'");
  return MCrQuery(TableName, query);
}

std::string
DatabaseManager::GetSerializedTableData(const std::string &TableName) {
  return GetModel(TableName)->ModelSerialization();
}

pqxx::result DatabaseManager::DeleteTable(const std::string &TableName,
                                          DatabaseQueryCommands QueryCommand) {
  std::string query;
  query.append(DatabaseCommandToString(QueryCommand)).append(TableName);
  return MCrQuery(TableName, query);
}
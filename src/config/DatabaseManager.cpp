#include "../../inc/Config/DatabaseManager.h"

DatabaseManager::DatabaseManager(const std::string &DatabaseConnectionString)
    : m_DatabaseConnectionString(DatabaseConnectionString) {
  m_DatabaseManager =
      std::make_shared<DatabaseConnection>(m_DatabaseConnectionString);
  APP_INFO("DATABASE CONNECTION INITIALIZED VIA THE DATABASE MANAGER");
}

DatabaseManager::~DatabaseManager() {
  m_DatabaseModels.clear();
  m_DatabaseManager.reset();
  APP_INFO("DATABASE MANAGER DESTROYED");
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
  APP_ERROR("OPERATOR [] ERROR / GET MODEL FUNCTION ERROR, MODEL NOT FOUND - " +
            ModelName);
  throw std::out_of_range("Model not found: " + ModelName);
}

std::shared_ptr<DatabaseModel> &
DatabaseManager::GetModel(const std::string &ModelName) {
  return (*this)[ModelName];
}

pqxx::result DatabaseManager::AddModel(const std::string &ModelName,
                                       const StringUnMap &ModelFields) {
  m_DatabaseModels.emplace_back(
      std::make_shared<DatabaseModel>(ModelName, ModelFields));
  auto Response = CreateTable(ModelName, ModelFields);
  APP_INFO("MODEL ADDED, TABLE CREATED - " + ModelName);
  return Response;
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
  APP_ERROR("MODEL NOT FOUND - " + ModelName);
  throw std::out_of_range("Model not found: " + ModelName);
}

pqxx::result DatabaseManager::TruncateModel(const std::string &ModelName) {
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
  APP_INFO("COLUMN ADDED, TABLE ALTERED - " + ModelName + " - " + FieldName);
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
  APP_INFO("COLUMN DROPED, TABLE ALTERED - " + ModelName + " - " + FieldName);
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
  APP_INFO("COLUMN ALTERED, TABLE ALTERED - " + ModelName + " - " + FieldName);
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
  APP_INFO("DATA INSERTED TO TABLE - " + ModelName);
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
  APP_INFO("COLUMN DATA UPDATED - " + ModelName);
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
  APP_INFO("COLUMNS DATA UPDATED - " + ModelName);
  return MCrQuery(ModelName, query);
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
    return Response;
  } catch (pqxx::sql_error const &e) {
    APP_ERROR("MCRQUERY ERROR AT TABLE - " + TableName + " " +
              std::string(e.what()));
    return {};
  } catch (std::exception const &e) {
    APP_ERROR("MCRQUERY GENERAL ERROR - " + std::string(e.what()));
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
  try {
    return MCrQuery(TableName, query);
  } catch (const std::exception &e) {
    APP_ERROR("ERROR AT CREATETABLE FUNCTION - " + TableName " - " +
              std::string(e.what()));
    return {};
  }
};

pqxx::result DatabaseManager::GetTableData(const std::string &TableName) {
  std::string query;
  query.append(DatabaseCommandToString(DatabaseQueryCommands::SelectAll))
      .append(TableName);
  try {
    return MCrQuery(TableName, query);
  } catch (const std::exception &e) {
    APP_ERROR("ERROR AT GETTABLEDATA1 FUNCTION - " + TableName + " - " +
              std::string(e.what()));
    return {};
  }
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
  try {
    return MCrQuery(TableName, query);
  } catch (const std::exception &e) {
    APP_ERROR("ERROR AT GETTABLEDATA2 FUNCTION - " + TableName + " - " +
              std::string(e.what()));
    return {};
  }
}

std::string
DatabaseManager::GetSerializedTableData(const std::string &TableName) {
  return GetModel(TableName)->ModelSerialization();
}

pqxx::result DatabaseManager::DeleteTable(const std::string &TableName,
                                          DatabaseQueryCommands QueryCommand) {
  std::string query;
  query.append(DatabaseCommandToString(QueryCommand)).append(TableName);
  try {
    if (std::is_same_v<decltype(QueryCommand),
                       decltype(DatabaseQueryCommands::DropDrop)>)
      APP_INFO("MODEL DELETED, TABLE DELETED - " + TableName);
    else {
      APP_INFO("MODEL MODIFIED, TABLE TRUNCATED - " + TableName);
    }
    return MCrQuery(TableName, query);
  } catch (const std::exception &e) {
    APP_ERROR("ERROR AT DELETETABLE FUNCION - " + TableName + " - " +
              std::string(e.what()));
    return {};
  }
}
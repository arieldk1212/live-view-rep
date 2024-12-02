#ifndef DATABASE_MODEL_H
#define DATABASE_MODEL_H

#include "../Core/UUID.h"

#include <unordered_map>

class DatabaseModel {
public:
  DatabaseModel(
      const std::string &ModelTabelName); // TODO: upon new model creation,
                                          // create a new table in the db.
  ~DatabaseModel() = default;

  void InsertField(const std::string &FieldType, const std::string &FieldValue);
  std::string StringSerialization();
  std::string QuerySerialization();
  // uint64_t GetObjectUUID();

private:
  int m_DatabaseModelSize;
  std::string m_DatabaseModelString;
  std::string m_DatabaseModelTableName;
  std::unordered_map<std::string, std::string> m_DatabaseModelFields;
};

// TODO: Manager->AddModel("LoggerModel", "fields") for example, creates the
// model that we want to create, puts it in the manager in a vector full of
// models and in every Model we can use the methods we created in DatabaseModel
// class.

#endif
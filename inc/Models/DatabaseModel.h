#ifndef DATABASE_MODEL_H
#define DATABASE_MODEL_H

#include "../Core/UUID.h"

#include <map>

using StringMap = std::map<std::string, std::string>;

class DatabaseModel {
public:
  DatabaseModel(const std::string &ModelName, const StringMap &ModelFields);
  ~DatabaseModel() = default;

  std::string GetModelName() const;
  std::string QuerySerialization();
  std::string ModelFieldsSerialization();
  std::string ModelSerialization();

  void ClearFields();
  void InsertField(const std::string &FieldType, const std::string &FieldValue);
  void ClearAndInsertFields(const StringMap &ModelFields);

private:
private:
  std::string m_DatabaseModelName;
  StringMap m_DatabaseModelFields;
};

#endif
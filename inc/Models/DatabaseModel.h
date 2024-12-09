#ifndef DATABASE_MODEL_H
#define DATABASE_MODEL_H

#include "../Core/UUID.h"

#include <map>

using StringMap = std::map<std::string, std::string>;

class DatabaseModel {
public:
  DatabaseModel(const std::string &ModelName, const StringMap &ModelFields);
  ~DatabaseModel() = default;

  const std::string GetModelName() const;
  std::string ModelSerialization();

  void ClearFields();
  void InsertField(const std::string &FieldName, const std::string &FieldType);
  void ClearAndInsertFields(const StringMap &ModelFields);

private:
private:
  std::string m_DatabaseModelName;
  StringMap m_DatabaseModelFields;
};

#endif
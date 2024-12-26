#ifndef DATABASE_MODEL_H
#define DATABASE_MODEL_H

#include "../Core/UUID.h"

#include <algorithm>
#include <map>

using StringMap = std::map<std::string, std::string>;

/**
 * @class DatabaseModel
 * @brief this class is responsible for the database model itself (table & fields) - api
 * @todo think about improvement when it comes to a small detail about the model - only edit.
 */
class DatabaseModel {
public:
  DatabaseModel(const std::string &ModelName, const StringMap &ModelFields);
  ~DatabaseModel() = default;

  const std::string &GetModelName() const;
  std::string ModelSerialization() const;

  /**
   * @brief clears the StringMap inside the class private member.
   */
  void ClearFields();
  /**
   * @brief inserts a new field in the model. 
   * @param FieldName - string, name of the field.
   * @param FieldType - string, type of the field.
   */
  void InsertField(const std::string &FieldName, const std::string &FieldType);
  /**
   * @brief clears and insert the new fields. 
   * @param ModelFields - StringMap, the new fields.
   */
  void ClearAndInsertFields(const StringMap &ModelFields);

private:
  std::string m_DatabaseModelName;
  StringMap m_DatabaseModelFields;
};

#endif
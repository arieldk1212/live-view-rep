#ifndef DATABASE_MODEL_H
#define DATABASE_MODEL_H

#include "../Config/Logger.h"
#include "../Core/UUID.h"

#include <algorithm>
#include <map>
#include <unordered_map>

using StringUnMap = std::unordered_map<std::string, std::string>;

/**
 * @class DatabaseModel
 * @brief this class is responsible for the database model itself (table &
 * fields) - api, no relation to postgres, only in project base.
 */
class DatabaseModel {
public:
  DatabaseModel(const std::string &ModelName, const StringUnMap &ModelFields);
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
   * @brief changes the field name.
   * @param FieldName - string, name of the field.
   * @param NewFieldName - string, name of the new field name.
   */
  void ChangeFieldName(const std::string &FieldName,
                       const std::string &NewFieldName);
  /**
   * @brief changes the field type, deletes data.
   * @param FieldName - string, name of the field.
   * @param FieldType - string, new field type.
   */
  void ChangeFieldType(const std::string &FieldName,
                       const std::string &FieldType);
  /**
   * @brief removes an existing field in an existing model.
   * @param FieldName string, name of the field to remove.
   */
  void RemoveField(const std::string &FieldName);
  /**
   * @brief clears and insert the new fields.
   * @param ModelFields - StringMap, the new fields.
  void ClearAndInsertFields(const StringUnMap &ModelFields);
   */

private:
  std::string m_DatabaseModelName;
  StringUnMap m_DatabaseModelFields;
};

#endif
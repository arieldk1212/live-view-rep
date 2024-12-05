#include "../../inc/Models/DatabaseModel.h"

DatabaseModel::DatabaseModel(const std::string &ModelTableName,
                             const StringMap &ModelFields)
    : m_DatabaseModelTableName{ModelTableName},
      m_DatabaseModelFields{ModelFields} {}
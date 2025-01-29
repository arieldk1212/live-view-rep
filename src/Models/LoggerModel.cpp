#include "../../inc/Models/LoggerModel.h"

LoggerModel::LoggerModel(std::shared_ptr<DatabaseManager> &Manager)
    : m_DatabaseManager(std::move(Manager)) {}


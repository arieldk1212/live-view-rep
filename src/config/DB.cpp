#include "../../inc/Config/DB.h"

DBConnection::DBConnection(const std::string &ConnectionString)
    : m_DBConnection(ConnectionString) {}
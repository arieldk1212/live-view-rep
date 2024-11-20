#ifndef DB_H
#define DB_H

#include "Logger.h"

#include <memory>
#include <pqxx/pqxx>

namespace DB {

typedef std::map<std::string, std::string> DBInfo;
typedef std::shared_ptr<pqxx::connection> DBPtr;

class DBConnection {
public:
	DBConnection();
	~DBConnection() = default;

	DBConnection(DBConnection &&) = delete;
	DBConnection(const DBConnection &other) = delete;
	DBConnection &operator=(DBConnection &&) = delete;
	DBConnection &operator=(const DBConnection &other) = delete;

	void CreateTable(const std::string &TableName);
	void WriteToTable(const std::string &TableName, const std::string &Data);
	bool TableExists(const std::string &TableName);
	void DeleteTable(const std::string &TabelName);

private:
	DBPtr m_DBConnection;
	DBInfo m_ConnectionInfo;
	std::string m_ConnectionString;
};
} // namespace DB

#endif
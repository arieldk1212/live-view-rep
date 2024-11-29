#include "../inc/App.h"

int main() {
  Logger::Init("");
  APP_INFO("APP LOGGER INITIALIZED");
  SYSTEM_INFO("SYSTEM LOGGER INITIALIZED");
  APP_INFO("APP INITIALIZED");
  SYSTEM_INFO("SYSTEM INITIALIZED");

  std::shared_ptr<DatabaseManager> Database = std::make_shared<DatabaseManager>();
  bool DatabaseStatus = Database->DatabaseConnectionValidation();
  Database->Query("insert into logger (logfile, timestamp, msg) values "
                        "('test', 'now', 'testttt');");
  if (DatabaseStatus) { SYSTEM_INFO("DATABASE CONNECTION ESTABLISHED"); }
}
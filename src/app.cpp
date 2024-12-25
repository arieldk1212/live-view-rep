#define ENABLE_LOGGING
#include "../inc/App.h"

int main() {
  GlobalConfig::InitGlobalConfig("../config.json");
  SYSTEM_INFO("CONFIG INITIALIZED");
  std::string DatabaseConnectionString = GlobalConfig::g_Config->DatabaseToString();

  Logger::Init(GlobalConfig::g_Config->LoggingPathToString());
  APP_INFO("APP LOGGER INITIALIZED");
  SYSTEM_INFO("SYSTEM LOGGER INITIALIZED");
  APP_INFO("APP INITIALIZED");
  SYSTEM_INFO("SYSTEM INITIALIZED");

  std::shared_ptr<DatabaseManager> Database =
      std::make_shared<DatabaseManager>(GlobalConfig::g_Config->DatabaseToString());
  bool DatabaseStatus = Database->DatabaseConnectionValidation();
  if (DatabaseStatus) {
    SYSTEM_INFO("DATABASE CONNECTION ESTABLISHED"); // TODO: test dtor in prod
  }
}
#define ENABLE_LOGGING
#include "../inc/App.h"

int main() {
  std::shared_ptr<Config> ConfigData = std::make_shared<Config>("../config.json");
  std::string DatabaseConnectionString = ConfigData->DatabaseToString();

  Logger::Init(ConfigData->LoggingPathToString());
  APP_INFO("APP LOGGER INITIALIZED");
  SYSTEM_INFO("SYSTEM LOGGER INITIALIZED");
  APP_INFO("APP INITIALIZED");
  SYSTEM_INFO("SYSTEM INITIALIZED");


  std::shared_ptr<DatabaseManager> Database =
      std::make_shared<DatabaseManager>(ConfigData->DatabaseToString());
  bool DatabaseStatus = Database->DatabaseConnectionValidation();
  if (DatabaseStatus) {
    SYSTEM_INFO("DATABASE CONNECTION ESTABLISHED"); // TODO: test dtor in prod
  }
}
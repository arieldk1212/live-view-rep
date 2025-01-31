#include "../inc/App.h"

int main() {
  GlobalConfig::InitGlobalConfig("../../config.json");
  Logger::Init(GlobalConfig::g_Config->LoggingPathToString());

  SYSTEM_INFO("CONFIG INITIALIZED");
  std::string DatabaseConnectionString =
      GlobalConfig::g_Config->DatabaseToString();

  APP_INFO("APP LOGGER INITIALIZED");
  SYSTEM_INFO("SYSTEM LOGGER INITIALIZED");
  APP_INFO("APP INITIALIZED");
  SYSTEM_INFO("SYSTEM INITIALIZED");

  auto Manager = std::make_shared<DatabaseManager>(DatabaseConnectionString);
}
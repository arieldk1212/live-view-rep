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

  AddressModel Addresses(Manager);
  Addresses.Init();
  /**
   * @bug DatabaseManager gets deleted before Address, therefore error
   * Fix It!
   * Manager gets nuklptr, remove move and make copy available.
   */
  // Manager->RemoveModel(Addresses.GetTableName());
}
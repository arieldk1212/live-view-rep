#include "../inc/App.h"

int main() {
  GlobalConfig::InitGlobalConfig("../../config.json");
  Logger::Init(GlobalConfig::g_Config->LoggingPathToString());

  SYSTEM_INFO("CONFIG INITIALIZED");
  auto DatabaseConnectionString = GlobalConfig::g_Config->DatabaseToString();

  APP_INFO("APP LOGGER INITIALIZED");
  SYSTEM_INFO("SYSTEM LOGGER INITIALIZED");
  APP_INFO("APP INITIALIZED");
  SYSTEM_INFO("SYSTEM INITIALIZED");

  auto Manager = std::make_shared<DatabaseManager>(DatabaseConnectionString);

  AddressModel Addresses(Manager);
  Addresses.Init();
  auto Result =
      Addresses.Add({{"addressname", "hamaasdasdasdasd"}, {"addressnumber", "18"}});

  Manager->RemoveModel(Addresses.GetTableName());
}
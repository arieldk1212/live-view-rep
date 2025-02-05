#include "../inc/App.h"

/**
 * @brief acts as the frontend of the application in "swift".
 * in this main function we demonstrate how the backend's api is being held.
 * further tests will be run here.
 */

int main() {

  /**
   * @warning when not in build, debug is in build/src
   * therefore the debugger is in /build/src, the terminal also needs
   * to be there to run without path errors.
   */
  std::filesystem::path ConfigPath = "../../configs/config.json";

  Logger::Init(Config::LoggingPathToString(ConfigPath));
  auto DatabaseConnectionString = Config::DatabaseToString(ConfigPath);

  APP_INFO("APP LOGGER INITIALIZED");
  SYSTEM_INFO("SYSTEM LOGGER INITIALIZED");

  APP_INFO("APP INITIALIZED");
  SYSTEM_INFO("SYSTEM INITIALIZED");

  auto Manager = std::make_shared<DatabaseManager>(DatabaseConnectionString);

  AddressModel Addresses(Manager);
  Addresses.Init();
  auto Result = Addresses.Add(
      {{"addressname", "hamaasdasdasdasd"}, {"addressnumber", "18"}});

  Manager->RemoveModel(Addresses.GetTableName());
}
#define ENABLE_LOGGING
#include "../inc/App.h"

int main() {
  Logger::Init("");
  APP_INFO("APP LOGGER INITIALIZED");
  SYSTEM_INFO("SYSTEM LOGGER INITIALIZED");
  APP_INFO("APP INITIALIZED");
  SYSTEM_INFO("SYSTEM INITIALIZED");

  std::shared_ptr<DatabaseManager> Database =
      std::make_shared<DatabaseManager>();
  bool DatabaseStatus = Database->DatabaseConnectionValidation();
  if (DatabaseStatus) {
    SYSTEM_INFO("DATABASE CONNECTION ESTABLISHED"); // TODO: test dtor in prod
  }
}
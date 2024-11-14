#include "../inc/App.h"
#include "Config/Logger.h"

int main() {
  Logger::Init();
  APP_INFO("APP LOGGER INITIALIZED");
  APP_INFO("APP INITIALIZED");
  APP_TRACE("APP RUNNING..");
  SYSTEM_ERROR("SYSTEM HEALTH CHECK");

  DB::DBConnection g_DB;
}
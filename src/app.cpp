#include "../inc/App.h"

int main() {
  Logger::Init();
  APP_INFO("LOGGER INITIALIZED");
  DB::DBConnection g_DB;

  APP_INFO("APP INITIALIZED");
  drogon::app().loadConfigFile("../config.json").run();

  return 0;
}
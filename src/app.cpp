#include "../inc/App.h"

int main() {
  Logger::Init();
  APP_INFO("APP LOGGER INITIALIZED");
  DB::DBConnection g_DB;

  APP_INFO("APP INITIALIZED");
  APP_TRACE("APP RUNNING..");

}
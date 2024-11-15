#include "../inc/App.h"

int main() {
  // TODO: need to figure out how to pass an empty string..
  Logger::Init("");
  APP_INFO("APP LOGGER INITIALIZED");
  SYSTEM_INFO("SYSTEM LOGGER INITIALIZED");
  APP_INFO("APP INITIALIZED");
  SYSTEM_INFO("SYSTEM INITIALIZED");

  DB::DBConnection g_DB;
}
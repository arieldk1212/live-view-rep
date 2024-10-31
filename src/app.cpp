#include "../inc/App.h"

int main () {

  Logger::Init();
  DB::DBConnection g_DB;
  APP_TRACE("APP INITIALIZED");

  return 0;
}
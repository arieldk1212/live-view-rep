#include "../inc/app.h"

int main () {

  Logger::Init();
  DBConnection g_DB;
  APP_TRACE("APP INITIALIZED");

  return 0;
}
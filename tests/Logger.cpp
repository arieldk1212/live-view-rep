#include "../inc/Config/Logger.h"

int main() {
  Logger::Init();
  APP_ERROR("Test");

  return 0;
}
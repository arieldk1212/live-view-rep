#include "../../inc/Config/GConfig.h"

namespace GlobalConfig {
std::shared_ptr<Config> g_Config;
}

void GlobalConfig::InitGlobalConfig(const std::filesystem::path &FilePath) {
  g_Config = std::make_shared<Config>(FilePath);
}
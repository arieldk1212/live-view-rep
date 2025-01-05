#ifndef GCONFIG_H
#define GCONFIG_H

#include "Config.h"

namespace GlobalConfig {
extern std::shared_ptr<Config> g_Config;
void InitGlobalConfig(const std::filesystem::path &FilePath);
} // namespace GlobalConfig

#endif
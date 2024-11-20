cmake_minimum_required(VERSION 3.24.2)
project(liveView VERSION 1.0 LANGUAGES CXX
  DESCRIPTION "Live View"
  HOMEPAGE_URL "https://github.com/arieldk1212/live-view")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") # g for lldb help

if (APPLE)
  set(CMAKE_TOOLCHAIN_FILE "/Users/$ENV{USER}/Library/vcpkg/scripts/buildsystems/vcpkg.cmake")
  set(CMAKE_PREFIX_PATH "/Users/$ENV{USER}/Library/vcpkg/installed/arm64-osx/share")
endif()

include_directories(inc)
include_directories(${OPENSSL_INCLUDE_DIR})

find_package(OpenSSL REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

set(PROJECT_LIBRARIES
libpqxx::pqxx
PostgreSQL::PostgreSQL
OpenSSL::SSL
OpenSSL::Crypto
spdlog::spdlog
Catch2::Catch2 Catch2::Catch2WithMain
)

add_subdirectory(src)
enable_testing()
add_subdirectory(tests)

target_link_libraries(src PRIVATE ${PROJECT_LIBRARIES})
target_link_libraries(tests PRIVATE ${PROJECT_LIBRARIES})
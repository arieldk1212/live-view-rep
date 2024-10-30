cmake_minimum_required(VERSION 3.24.2)
project(liveView LANGUAGES CXX
  DESCRIPTION "Live View"
  HOMEPAGE_URL "https://github.com/arieldk1212/live-view")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -g") # g for lldb help

if (APPLE)
  set(CMAKE_TOOLCHAIN_FILE "/Users/$ENV{USER}/Library/vcpkg/scripts/buildsystems/vcpkg.cmake")
  set(CMAKE_PREFIX_PATH "/Users/$ENV{USER}/Library/vcpkg/installed/arm64-osx/share")
endif()

include_directories(inc)
add_subdirectory(src)

find_package(OpenSSL REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Drogon CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR})

target_link_libraries(src PRIVATE Drogon::Drogon libpqxx::pqxx PostgreSQL::PostgreSQL OpenSSL::SSL OpenSSL::Crypto spdlog::spdlog)
target_link_libraries(app PRIVATE Drogon::Drogon libpqxx::pqxx PostgreSQL::PostgreSQL OpenSSL::SSL OpenSSL::Crypto spdlog::spdlog)
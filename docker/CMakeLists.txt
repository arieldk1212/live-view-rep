cmake_minimum_required(VERSION 3.24.2)
project(liveView LANGUAGES CXX
  DESCRIPTION "Live View"
  HOMEPAGE_URL "https://github.com/arieldk1212/live-view")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(CMAKE_PREFIX_PATH "/usr/local/vcpkg/installed/buildsystems/vcpkg.cmake")

include_directories(inc)
add_subdirectory(src)

find_package(PostgreSQL REQUIRED)
find_package(asio CONFIG REQUIRED)
find_package(Crow CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)

target_link_libraries(src PRIVATE Crow::Crow asio::asio libpqxx::pqxx PostgreSQL::PostgreSQL)
target_link_libraries(app PRIVATE Crow::Crow asio::asio libpqxx::pqxx PostgreSQL::PostgreSQL)
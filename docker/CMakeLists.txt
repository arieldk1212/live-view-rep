cmake_minimum_required(VERSION 3.24.2)
project(liveView LANGUAGES CXX
  DESCRIPTION "Live View"
  HOMEPAGE_URL "https://github.com/arieldk1212/live-view")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(inc)
add_subdirectory(src)

file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.3/CPM.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
  EXPECTED_HASH SHA256=cc155ce02e7945e7b8967ddfaff0b050e958a723ef7aad3766d368940cb15494
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

CPMAddPackage("https://github.com/chriskohlhoff/asio/archive/refs/tags/asio-1-31-0.zip")
set(ASIO_INCLUDE_DIR /live-view/build/_deps/asio-1-31-src/asio/include)
CPMAddPackage("gh:CrowCpp/Crow#v1.2.0")
CPMAddPackage("gh:jtv/libpqxx#7.9.2")

include_directories(${ASIO_INCLUDE_DIR})
target_link_libraries(src PRIVATE Crow::Crow libpqxx::pqxx)
target_link_libraries(app PRIVATE Crow::Crow libpqxx::pqxx)
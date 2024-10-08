cmake_minimum_required(VERSION 3.30)
project(liveView LANGUAGES CXX
  DESCRIPTION "Live View"
  HOMEPAGE_URL "https://github.com/arieldk1212/live-view")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(inc)

find_package(asio REQUIRED)
include_directories(${asio_DIR})
target_link_libraries(src PRIVATE asio)

add_subdirectory(src)
add_subdirectory(lib/Crow)

enable_testing()
add_subdirectory(test)
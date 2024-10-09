cmake_minimum_required(VERSION 3.30)
project(liveView LANGUAGES CXX
  DESCRIPTION "Live View"
  HOMEPAGE_URL "https://github.com/arieldk1212/live-view")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_TOOLCHAIN_FILE "/Users/arielkriheli/Library/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_PREFIX_PATH "/Users/arielkriheli/Library/vcpkg/installed/arm64-osx/share")

include_directories(inc)
add_subdirectory(src)

find_package(Crow CONFIG REQUIRED)
target_link_libraries(src PRIVATE Crow::Crow asio::asio)
target_link_libraries(app PRIVATE Crow::Crow asio::asio)
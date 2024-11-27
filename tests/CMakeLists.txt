enable_testing()
find_package(GTest CONFIG REQUIRED)

add_library(tests
Config/Database/Database.cpp
Config/Logger/Logger.cpp
)

add_library(TestLib INTERFACE)
target_link_libraries(TestLib INTERFACE ${PROJECT_LIBRARIES})

include(GoogleTest)

add_executable(LoggerTest Config/Logger/Logger.cpp)
add_executable(DatabaseTest Config/Database/Database.cpp)


target_link_libraries(LoggerTest PRIVATE TestLib GTest::gtest_main src)
target_link_libraries(DatabaseTest PRIVATE TestLib GTest::gtest_main src)

gtest_discover_tests(LoggerTest)
gtest_discover_tests(DatabaseTest)
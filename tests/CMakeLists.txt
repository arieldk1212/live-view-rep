set(LOGGER_TEST Config/Logger/Logger.cpp)

add_library(
tests
${LOGGER_TEST}
)

add_executable(LoggerTest ${LOGGER_TEST})
target_link_libraries(LoggerTest PRIVATE src ${PROJECT_LIBRARIES})
add_test(NAME LoggerTest COMMAND LoggerTest)
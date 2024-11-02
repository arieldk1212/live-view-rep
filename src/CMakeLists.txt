set(SOURCES
App.cpp
Config/Logger.cpp
Config/DB.cpp
)

add_library(src ${SOURCES})

add_executable(App ${SOURCES})

target_link_libraries(App PRIVATE ${PROJECT_LIBRARIES})
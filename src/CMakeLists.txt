set(SOURCES
App.cpp
Config/Logger.cpp
Config/DB.cpp
)

add_library(src ${SOURCES})

add_executable(App ${SOURCES})
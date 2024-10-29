set(SOURCES
app.cpp
config/logger.cpp
config/db_connection.cpp
)

add_library(src ${SOURCES})

add_executable(app ${SOURCES})
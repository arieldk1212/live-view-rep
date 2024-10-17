set(SOURCES
app.cpp
db/sql_connection.cpp
config/env.cpp
config/logger.cpp
)

add_library(src ${SOURCES})

add_executable(app ${SOURCES})
set(SOURCES
app.cpp
db/sql_connection.cpp
)

add_library(src ${SOURCES})

add_executable(app ${SOURCES})
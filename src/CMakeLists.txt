set(SOURCES
App.cpp
Address.cpp
Config/Logger.cpp
Config/Database.cpp
Config/DatabaseManager.cpp
Core/Entity.cpp
Core/Type.cpp
Core/UUID.cpp
Core/Geo.cpp
)

add_library(src STATIC ${SOURCES})

# add_executable(App App.cpp)
add_executable(App ${SOURCES})

target_link_libraries(App PRIVATE src ${PROJECT_LIBRARIES})
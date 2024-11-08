set(SOURCES
App.cpp
Address.cpp
Config/Logger.cpp
Config/DB.cpp
Core/Entity.cpp
Core/Type.cpp
Core/UUID.cpp
Core/Geo.cpp
)

add_library(src ${SOURCES})

add_executable(App ${SOURCES})

target_link_libraries(App PRIVATE ${PROJECT_LIBRARIES})
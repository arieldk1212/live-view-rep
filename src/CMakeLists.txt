list(APPEND sources
App.cpp

Config/Logger.cpp
Config/Database.cpp
Config/DatabaseManager.cpp
Config/Config.cpp

Core/UUID.cpp
Core/Geo.cpp

Models/LogModel.cpp
Models/AddressModel.cpp
)

add_library(src STATIC ${sources})

add_executable(App ${sources})

target_link_libraries(App PRIVATE src ${project_libraries})
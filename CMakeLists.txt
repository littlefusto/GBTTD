cmake_minimum_required(VERSION 3.22)
project(GBTTD)

set(CMAKE_CXX_STANDARD 17)
add_executable(GBTTD main.cpp 02_Domain/Textures.h 02_Domain/Domain.h 00_Game/Tiles/Tile.cpp 00_Game/Tiles/Tile.h)

find_package(SFML REQUIRED system window graphics network audio)
if(SFML_FOUND)
    target_link_libraries(GBTTD sfml-graphics)
    target_link_libraries(GBTTD sfml-window)
    target_link_libraries(GBTTD sfml-audio)
    target_link_libraries(GBTTD sfml-network)
    target_link_libraries(GBTTD sfml-system)
endif()
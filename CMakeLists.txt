cmake_minimum_required(VERSION 3.22)
project(GBTTD)

set(CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_NAME "GBTTD")
add_executable(GBTTD main.cpp)

find_package(SFML REQUIRED system window graphics network audio)
if(SFML_FOUND)
    target_link_libraries(GBTTD sfml-graphics)
    target_link_libraries(GBTTD sfml-window)
    target_link_libraries(GBTTD sfml-audio)
    target_link_libraries(GBTTD sfml-network)
    target_link_libraries(GBTTD sfml-system)
    #target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})

endif()
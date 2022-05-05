cmake_minimum_required(VERSION 3.22)
project(GBTTD)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 1.6 REQUIRED system window graphics network audio)
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})

add_executable(GBTTD main.cpp)

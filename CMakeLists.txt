cmake_minimum_required(VERSION 3.20)
project(GBTTD)

set(CMAKE_CXX_STANDARD 17)
set(SRC_DIRS ${CMAKE_SOURCE_DIR}
        "00_Game"
        "00_Game/Tiles"

        "01_Graphics"

        "02_Domain"

        "03_Saves"
        )

# Get all src files
set(SRC_FILES "")
set(INCLUDE_FILES "")
FOREACH(DIR IN LISTS SRC_DIRS)
    file(GLOB SOURCES "${DIR}/*.cpp")
    set(SRC_FILES ${SRC_FILES} ${SOURCES})
    file(GLOB SOURCES "${DIR}/*.h")
    set(INCLUDE_FILES ${INCLUDE_FILES} ${SOURCES})
ENDFOREACH(DIR)

add_executable(GBTTD ${SRC_FILES})
target_include_directories(GBTTD PRIVATE ${SRC_DIRS})

set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED system window graphics network audio)
if(SFML_FOUND)
    target_link_libraries(GBTTD sfml-graphics)
    target_link_libraries(GBTTD sfml-window)
    target_link_libraries(GBTTD sfml-audio)
    target_link_libraries(GBTTD sfml-network)
    target_link_libraries(GBTTD sfml-system)
endif()
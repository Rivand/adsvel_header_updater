cmake_minimum_required(VERSION 3.7)

project(adsvel_header_updater)

set(CMAKE_CXX_STANDARD 17)

add_executable (${PROJECT_NAME}
    "file_list_reader.h"
    "file_list_reader.cpp"
    "file_updater.h"
    "file_updater.cpp"
    "main.cpp"
    )

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} stdc++fs)

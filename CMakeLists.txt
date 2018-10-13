cmake_minimum_required(VERSION 3.7)

project(SdHeaderUpdater)

set(CMAKE_CXX_FLAGS                 "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -pthread ")
set(CMAKE_CXX_FLAGS_DEBUG           "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -pthread -g -DDREAL_DEBUG -DDREAL_TRACE -fno-inline")
set(CMAKE_CXX_FLAGS_MINSIZEREL      "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -pthread -Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE         "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -pthread -O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -pthread -O2 -g")

# boost.
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_MULTITHREADED OFF)
find_package(Boost REQUIRED system filesystem)
include_directories (SYSTEM ${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARIES})


add_executable (${PROJECT_NAME}
    "file_list_reader.h"
    "file_list_reader.cpp"
    "file_updater.h"
    "file_updater.cpp"
    "main.cpp"
    )

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

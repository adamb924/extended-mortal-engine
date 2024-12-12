cmake_minimum_required(VERSION 3.16)

project(extended-mortal-engine LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core )
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core )

# Use generator expressions to add the "d" suffix in Debug mode
find_library(MORTALENGINE_LIB_RELEASE NAMES mortalengine)
find_library(MORTALENGINE_LIB_DEBUG NAMES mortalengined)

message(STATUS "MORTALENGINE_LIB_RELEASE = ${MORTALENGINE_LIB_RELEASE}")
message(STATUS "MORTALENGINE_LIB_DEBUG = ${MORTALENGINE_LIB_DEBUG}")

add_executable(extended-mortal-engine
        main.cpp 
        numberofprecedinglettersiseven.cpp 
        reduplicator.cpp
)

target_include_directories(extended-mortal-engine PUBLIC
    "."
    ${CMAKE_PREFIX_PATH}/include/mortal-engine
)

target_link_libraries(extended-mortal-engine
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    $<$<CONFIG:Debug>:${MORTALENGINE_LIB_DEBUG}>
    $<$<NOT:$<CONFIG:Debug>>:${MORTALENGINE_LIB_RELEASE}>
)

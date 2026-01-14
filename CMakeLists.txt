cmake_minimum_required(VERSION 3.25.1)
project(minilog C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB SOURCE "${SOURCE_DIR}/*.c")

add_compile_options(-Wall -Wextra -Werror -pedantic)

add_library(${PROJECT_NAME} STATIC ${SOURCE})

target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCE_DIR})

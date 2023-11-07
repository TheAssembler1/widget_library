cmake_minimum_required(VERSION 3.16.3)

project(
  WidgetApp
  VERSION 1.0
  LANGUAGES CXX)

find_package(SDL2 REQUIRED)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
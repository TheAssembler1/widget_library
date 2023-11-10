cmake_minimum_required(VERSION 3.16.3)

project(
  WidgetApp
  VERSION 1.0
  LANGUAGES CXX
)

if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
	set(CPU_ARCH "x64")
else()
	set(CPU_ARCH "x86")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

if(WIN32)
	# https://github.com/libsdl-org/SDL/releases/download/release-2.0.20/SDL2-devel-2.0.20-VC.zip
	set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/dep/lib/${CPU_ARCH}/SDL2.lib")
	set(SDL_DLL  "${CMAKE_CURRENT_LIST_DIR}/dep/lib/${CPU_ARCH}/SDL2.dll")

	file(COPY ${SDL_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

	include_directories("${CMAKE_CURRENT_LIST_DIR}/dep/include/SDL2")
elseif(UNIX)
	# sudo apt install libsdl2-dev
	find_package(SDL2 REQUIRED)
endif()

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

set(CMAKE_BUILD_TYPE Debug)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
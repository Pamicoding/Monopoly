cmake_minimum_required(VERSION 3.23)
project(Monopoly)

include_directories(${CMAKE_SOURCE_DIR}/monopoly)
include_directories(${CMAKE_SOURCE_DIR}/monopoly/include)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/vendor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message("COMPILER = ${CMAKE_CXX_COMPILER_ID}")
message("BUILD_DIR = ${CMAKE_BINARY_DIR}")
message("SOURCE_DIR = ${CMAKE_SOURCE_DIR}")

file(GLOB MAIN ${CMAKE_SOURCE_DIR}/monopoly/*.cpp ${CMAKE_SOURCE_DIR}/monopoly/*.hpp)
file(GLOB CARD_MODULE ${CMAKE_SOURCE_DIR}/monopoly/Cards/*.cpp ${CMAKE_SOURCE_DIR}/monopoly/Cards/*.hpp)
file(GLOB GAME_MODULE ${CMAKE_SOURCE_DIR}/monopoly/Game/*.cpp ${CMAKE_SOURCE_DIR}/monopoly/Game/*.hpp)
file(GLOB MINI_GAME_MODULE ${CMAKE_SOURCE_DIR}/monopoly/MiniGames/*.cpp ${CMAKE_SOURCE_DIR}/monopoly/MiniGames/*.hpp)
file(GLOB TILE_MODULE ${CMAKE_SOURCE_DIR}/monopoly/Tiles/*.cpp ${CMAKE_SOURCE_DIR}/monopoly/Tiles/*.hpp)
file(GLOB UTIL_MODULE ${CMAKE_SOURCE_DIR}/monopoly/Utils/*.cpp ${CMAKE_SOURCE_DIR}/monopoly/Utils/*.hpp)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Debug)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -glldb -fstandalone-debug -fdebug-macro")
  endif()
  if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  endif()
endif()

add_executable(monopoly
  ${MAIN}
  ${CARD_MODULE}
  ${GAME_MODULE}
  ${MINI_GAME_MODULE}
  ${TILE_MODULE}
  ${UTIL_MODULE}
)

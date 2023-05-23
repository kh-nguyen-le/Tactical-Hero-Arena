cmake_minimum_required(VERSION 3.1)
project(TacticalHeroArena)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CADMIUM_ROOT ~/cadmium_v2)

add_library(cadmium INTERFACE)
target_include_directories(cadmium INTERFACE ${CADMIUM_ROOT}/include/ ${CADMIUM_ROOT}/json/include)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(model)
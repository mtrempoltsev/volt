cmake_minimum_required(VERSION 3.4)

project(volt-console)

get_filename_component(VOLT_CONSOLE_ROOT "${CMAKE_SOURCE_DIR}" ABSOLUTE)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(VOLT_DEBUG ON)
    set(VOLT_BIN_DIR "${VOLT_CONSOLE_ROOT}/bin/Debug")
    set(VOLT_LIB_DIR "${VOLT_CONSOLE_ROOT}/bin/Debug")
    set(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "" FORCE)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(VOLT_RELEASE ON)
    set(VOLT_BIN_DIR "${VOLT_CONSOLE_ROOT}/bin/Release")
    set(VOLT_LIB_DIR "${VOLT_CONSOLE_ROOT}/bin/Release")
    set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)
else()
    message(FATAL_ERROR "Invalid CMAKE_BUILD_TYPE value (Debug|Release)")
endif()

message(STATUS "binaries output: " ${VOLT_BIN_DIR})
message(STATUS "libraries output: " ${VOLT_LIB_DIR})

# ---------------------------- paths ----------------------------
set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY_DEBUG ${VOLT_BIN_DIR})
set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY_RELEASE ${VOLT_BIN_DIR})
set(CMAKE_EXECUTABLE_OUTPUT_PATH ${VOLT_BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${VOLT_LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${VOLT_LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_PATH ${VOLT_LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${VOLT_BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${VOLT_BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${VOLT_BIN_DIR})

#----------------------- compile options ------------------------
set(CMAKE_CXX_STANDARD 14)

# ------------------------ 3rd-parties --------------------------
set(VOLT_CONSOLE_3RD_PARTY "${VOLT_CONSOLE_ROOT}/../../3rd-party")

#----------------------------- cmake ----------------------------
list(APPEND CMAKE_MODULE_PATH "${VOLT_CONSOLE_3RD_PARTY}/cotire/CMake")
list(APPEND CMAKE_MODULE_PATH "${VOLT_CONSOLE_3RD_PARTY}/cmake")
include(cotire)
include(source_group)
include(use_fmt)
include(use_yal)

use_fmt("${VOLT_CONSOLE_3RD_PARTY}")
use_yal("${VOLT_CONSOLE_3RD_PARTY}")

# ---------------------------- boost ----------------------------
find_package(Boost COMPONENTS
    filesystem
    system
    REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# --------------------------- sources ---------------------------
set(HEADERS
    src/stdafx.h
    )

set(SOURCES
    src/stdafx.cpp

    src/main.cpp
    )

# ----------------------- subdirectories ------------------------
add_subdirectory(../core core)

set_source_group("Header Files" ${SUBPROJECT_ROOT}/src ${HEADERS})
set_source_group("Source Files" ${SUBPROJECT_ROOT}/src ${SOURCES})

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT src/stdafx.h)
cotire(${PROJECT_NAME})

target_link_libraries (${PROJECT_NAME}
    yal
    fmt
    volt-client-core
    ${Boost_LIBRARIES}
    )

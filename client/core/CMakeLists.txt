cmake_minimum_required(VERSION 3.4)

set(VOLT_CORE_PROJECT volt-client-core)

project(${VOLT_CORE_PROJECT})

get_filename_component(VOLT_CORE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)

#----------------------- compile options ------------------------
set(CMAKE_CXX_STANDARD 14)

# ------------------------ 3rd-parties --------------------------
set(VOLT_CORE_3RD_PARTY "${VOLT_CORE_ROOT}/../../3rd-party")

#----------------------------- cmake ----------------------------
list(APPEND CMAKE_MODULE_PATH "${VOLT_CORE_3RD_PARTY}/cotire/CMake")
list(APPEND CMAKE_MODULE_PATH "${VOLT_CORE_3RD_PARTY}/cmake")
include(cotire)
include(source_group)
include(use_fmt)
include(use_gtest)
include(use_rapidjson)
include(use_yal)

# ---------------------------- boost ----------------------------
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS
    filesystem
    system
    REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# ----------------------------- fmt -----------------------------
use_fmt("${VOLT_CONSOLE_3RD_PARTY}")

# ---------------------------- gtest ----------------------------
use_gtest("${VOLT_CONSOLE_3RD_PARTY}")

# -------------------------- rapidjson --------------------------
use_rapidjson("${VOLT_CONSOLE_3RD_PARTY}")

# ----------------------------- yal -----------------------------
use_yal("${VOLT_CONSOLE_3RD_PARTY}")

# -------------------------- threads ----------------------------
find_package(Threads)

# -------------------------- OpenSSL ----------------------------
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
message(${OPENSSL_FOUND})

# --------------------------- sources ---------------------------
set(HEADERS
    )

set(SOURCES
    src/stdafx.h
    src/stdafx.cpp
    )

set_source_group("Header Files" ${SUBPROJECT_ROOT}/src ${HEADERS})
set_source_group("Source Files" ${SUBPROJECT_ROOT}/src ${SOURCES})

set(VOLT_CORE_INCLUDE ${VOLT_CORE_ROOT}/include)

include_directories(${VOLT_CORE_INCLUDE})

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT src/stdafx.h)
cotire(${PROJECT_NAME})

set(VOLT_CORE_TEST_PROJECT test_${PROJECT_NAME})

add_test(NAME ${VOLT_CORE_TEST_PROJECT} COMMAND ${VOLT_CORE_TEST_PROJECT})

add_subdirectory(tests)

enable_testing()

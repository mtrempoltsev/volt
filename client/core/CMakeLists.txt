cmake_minimum_required(VERSION 3.4)

project(volt-client-core)

get_filename_component(VOLT_CORE_ROOT "${CMAKE_SOURCE_DIR}" ABSOLUTE)

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
include(use_rapidjson)
include(use_yal)

# ---------------------------- boost ----------------------------
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS
    system
    REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# ----------------------------- fmt -----------------------------
use_fmt("${VOLT_CONSOLE_3RD_PARTY}")

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
    src/stdafx.h
    )

set(SOURCES
    src/stdafx.cpp
    )

set_source_group("Header Files" ${SUBPROJECT_ROOT}/src ${HEADERS})
set_source_group("Source Files" ${SUBPROJECT_ROOT}/src ${SOURCES})

include_directories(include/)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT src/stdafx.h)
cotire(${PROJECT_NAME})

target_link_libraries (${PROJECT_NAME}
    yal
    fmt
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${OPENSSL_LIBRARIES}
    )

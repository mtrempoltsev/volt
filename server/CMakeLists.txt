cmake_minimum_required(VERSION 3.4)

project(volt-server)

get_filename_component(VOLT_ROOT "${CMAKE_SOURCE_DIR}" ABSOLUTE)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(VOLT_DEBUG ON)
    set(VOLT_BIN_DIR "${VOLT_ROOT}/bin/Debug")
    set(VOLT_LIB_DIR "${VOLT_ROOT}/bin/Debug")
    set(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "" FORCE)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(VOLT_RELEASE ON)
    set(VOLT_BIN_DIR "${VOLT_ROOT}/bin/Release")
    set(VOLT_LIB_DIR "${VOLT_ROOT}/bin/Release")
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
set(VOLT_3RD_PARTY "${VOLT_ROOT}/../3rd-party")

# ----------------------- source groups  ------------------------
macro(set_source_group group_name root_dir ${ARGN})
    get_filename_component(_path ${root_dir} ABSOLUTE)
    foreach(_source IN ITEMS ${ARGN})
        get_filename_component(_source_path "${_source}" PATH)
        string(REPLACE "${_path}" "" _source_trimmed "${_source_path}")
        set(_source_group "${group_name}${_source_trimmed}")
        string(REPLACE "/" "\\" _source_group "${_source_group}")
        source_group("${_source_group}" FILES "${_source}")
    endforeach()
endmacro()

# ---------------------------- boost ----------------------------
find_package(Boost COMPONENTS
    system
    REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

#----------------------------- cmake ----------------------------
list(APPEND CMAKE_MODULE_PATH "${VOLT_3RD_PARTY}/cotire/CMake")
list(APPEND CMAKE_MODULE_PATH "${VOLT_3RD_PARTY}/cmake")
include(cotire)

# -------------------------- threads ----------------------------
find_package(Threads)

# -------------------------- OpenSSL ----------------------------
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
message(${OPENSSL_FOUND})

# --------------------------- gtest -----------------------------
set(BUILD_GMOCK         OFF CACHE BOOL "Builds the googlmock" FORCE)
set(BUILD_GTEST         ON  CACHE BOOL "Builds the googletest" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory("${VOLT_3RD_PARTY}/google-test" google-test)
include_directories("${VOLT_3RD_PARTY}/google-test/googletest/include")

# ---------------------------- fmt ------------------------------
set(FMT_PEDANTIC        OFF CACHE BOOL "Fmt pedantic" FORCE)
set(FMT_DOC             OFF CACHE BOOL "Generate Fmt doc" FORCE)
set(FMT_INSTALL         OFF CACHE BOOL "Install Fmt" FORCE)
set(FMT_TEST            OFF CACHE BOOL "Test Fmt" FORCE)
set(FMT_USE_CPP11       ON  CACHE BOOL "Fmt use C++11" FORCE)
add_subdirectory("${VOLT_3RD_PARTY}/fmt" fmt)
include_directories("${VOLT_3RD_PARTY}/fmt")

# ---------------------------- yal ------------------------------
set(YAL_BUILD_FMTLIB    OFF CACHE BOOL "Build Fmt" FORCE)
set(YAL_BUILD_GTEST     OFF CACHE BOOL "Build Gtest" FORCE)
set(YAL_BUILD_TESTS     OFF CACHE BOOL "Build YAL tests" FORCE)
set(YAL_BUILD_EXAMPLES  OFF CACHE BOOL "Build YAL examples" FORCE)
add_subdirectory("${VOLT_3RD_PARTY}/yal" yal)
include_directories("${VOLT_3RD_PARTY}/yal/include")

# --------------------------- sources ---------------------------
set(HEADERS
    src/stdafx.h
    ../shared/crypto/dsa.h
    )

set(SOURCES
    ../shared/crypto/dsa.cpp
    src/stdafx.cpp

    src/main.cpp
    )

set_source_group("sources" ${SUBPROJECT_ROOT} ${HEADERS} ${SOURCES})

include_directories(include/)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT src/stdafx.h)
cotire(${PROJECT_NAME})

target_link_libraries (${PROJECT_NAME}
    yal
    fmt
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${OPENSSL_LIBRARIES}
    )

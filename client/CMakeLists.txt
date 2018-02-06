cmake_minimum_required(VERSION 3.4)

project(volt-client)

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
    message(FATAL_ERROR "please add -DCMAKE_BUILD_TYPE=(Debug|Release)")
endif()

if(NOT CMAKE_GENERATOR_PLATFORM OR NOT ${CMAKE_GENERATOR_PLATFORM} STREQUAL "x64")
    message(FATAL_ERROR "please add -DCMAKE_GENERATOR_PLATFORM=x64")
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

if(MSVC14)
    set(VOLT_PLATFORM msvc2015x64)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /W4")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W4")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ignore:4099")
elseif(APPLE)
    set(VOLT_PLATFORM mac)
    set(CLANG ON)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wpedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wpedantic")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(VOLT_PLATFORM linux)
    set(GCC ON)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wpedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wpedantic")
else()
    message(FATAL_ERROR "Unknown platform")
endif()

message(STATUS "platform: " ${VOLT_PLATFORM})

# ------------------------- externals ---------------------------
get_filename_component(VOLT_EXTERNALS "${VOLT_ROOT}/../externals" ABSOLUTE)

# ---------------------------- boost ----------------------------
set(VOLT_BOOST_ROOT "${VOLT_EXTERNALS}/boost-1.66.0")
set(BOOST_INCLUDEDIR "${VOLT_BOOST_ROOT}/include")
set(BOOST_LIBRARYDIR "${VOLT_BOOST_ROOT}/lib/${VOLT_PLATFORM}")
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_NO_SYSTEM_PATHS ON)
find_package(Boost 1.66 REQUIRED COMPONENTS
    locale
    filesystem
    system)
include_directories(${Boost_INCLUDE_DIRS})
add_definitions(-DBOOST_ALL_NO_LIB)

# ----------------------------- fmt -----------------------------
set(VOLT_FMT_ROOT "${VOLT_EXTERNALS}/fmt-4.1.0")
set(VOLT_FMT_LIB_DIR "${VOLT_FMT_ROOT}/lib/${VOLT_PLATFORM}")
set(VOLT_FMT_LIBRARIES
    optimized "${VOLT_FMT_LIB_DIR}/fmt.lib"
    debug "${VOLT_FMT_LIB_DIR}/fmtd.lib")
set(FMT_LIBRARIES ${VOLT_FMT_LIBRARIES})
include_directories("${VOLT_FMT_ROOT}/include")

# ---------------------------- gtest ----------------------------
set(VOLT_GTEST_ROOT "${VOLT_EXTERNALS}/googletest-1.8.0")
set(VOLT_GTEST_LIB_DIR "${VOLT_GTEST_ROOT}/lib/${VOLT_PLATFORM}")
set(VOLT_GTEST_LIBRARIES
    optimized "${VOLT_GTEST_LIB_DIR}/gtest.lib"
    debug "${VOLT_GTEST_LIB_DIR}/gtestd.lib")
include_directories("${VOLT_GTEST_ROOT}/include")

# ----------------------------- lz4 -----------------------------
set(VOLT_LZ4_ROOT "${VOLT_EXTERNALS}/lz4-1.8.1.2")
set(VOLT_LZ4_LIB_DIR "${VOLT_LZ4_ROOT}/lib/${VOLT_PLATFORM}")
set(VOLT_LZ4_LIBRARIES
    optimized "${VOLT_LZ4_LIB_DIR}/liblz4.lib"
    debug "${VOLT_LZ4_LIB_DIR}/liblz4d.lib")
include_directories("${VOLT_LZ4_ROOT}/include")

# --------------------------- openssl ---------------------------
set(VOLT_OPENSSL_ROOT "${VOLT_EXTERNALS}/openssl-1.1.0f")
set(VOLT_OPENSSL_LIB_DIR "${VOLT_OPENSSL_ROOT}/lib/${VOLT_PLATFORM}")
set(OPENSSL_FOUND TRUE)
set(OPENSSL_INCLUDE_DIR "${VOLT_OPENSSL_ROOT}/include")
set(OPENSSL_CRYPTO_LIBRARY
    optimized "${VOLT_OPENSSL_LIB_DIR}/libcryptoMT.lib"
    debug "${VOLT_OPENSSL_LIB_DIR}/libcryptoMTd.lib")
set(OPENSSL_SSL_LIBRARY
    optimized "${VOLT_OPENSSL_LIB_DIR}/libsslMT.lib"
    debug "${VOLT_OPENSSL_LIB_DIR}/libsslMTd.lib")
set(OPENSSL_LIBRARIES ${OPENSSL_CRYPTO_LIBRARY} ${OPENSSL_SSL_LIBRARY})
set(OPENSSL_VERSION "1.1.0f")
include_directories("${OPENSSL_INCLUDE_DIR}")

# ------------------------- rapidjson ---------------------------
set(VOLT_RAPIDJSON_ROOT "${VOLT_EXTERNALS}/rapidjson-1.1.0")
include_directories("${VOLT_RAPIDJSON_ROOT}/include")

# -------------------------- threads ----------------------------
find_package(Threads)

# --------------------------- libs ------------------------------
get_filename_component(VOLT_LIBS "${VOLT_ROOT}/../libs" ABSOLUTE)

# --------------------------- pods ------------------------------
set(VOLT_PODS_ROOT "${VOLT_LIBS}/pods")
include_directories("${VOLT_PODS_ROOT}/include")

# --------------------------- yal -------------------------------
set(VOLT_YAL_ROOT "${VOLT_LIBS}/yal/")
set(YAL_BUILD_FMTLIB OFF CACHE BOOL "Build Fmt" FORCE)
set(YAL_BUILD_GTEST OFF CACHE BOOL "Build Gtest" FORCE)
set(YAL_BUILD_TESTS OFF CACHE BOOL "Build YAL tests" FORCE)
set(YAL_BUILD_EXAMPLES OFF CACHE BOOL "Build YAL examples" FORCE)
add_subdirectory("${VOLT_YAL_ROOT}" yal)
set(VOLT_YAL_LIB yal)
include_directories("${VOLT_YAL_ROOT}/include")

# ------------------------ source groups  -----------------------
macro(set_source_group ${ARGN})
    foreach(_item IN ITEMS ${ARGN})
        get_filename_component(_name "${_item}" NAME)
        string(REPLACE "${_name}" "" _path "${_item}")
        string(REPLACE "/" "\\" _path "${_path}")
        source_group("${_path}" FILES "${_item}")
    endforeach()
endmacro()

# ------------------------- precompiled  ------------------------
if(MSVC)
    macro(use_precompiled_header pch_dir ${ARGN})
        set(_pch_bin "${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}.${PROJECT_NAME}.pch")
        set(_pch_h ${pch_dir}/stdafx.h)
        set(_pch_cpp ${pch_dir}/stdafx.cpp)
        foreach(_source IN ITEMS ${ARGN})
            set_source_files_properties(${_source} PROPERTIES
                COMPILE_FLAGS "/Yu\"${_pch_h}\" /Fp\"${_pch_bin}\" /FI\"${_pch_h}\""
                OBJECT_DEPENDS "${_pch_bin}")
        endforeach()
        set_source_files_properties("${_pch_cpp}" PROPERTIES
            COMPILE_FLAGS "/Yc\"stdafx.h\" /Fp\"${_pch_bin}\""
            OBJECT_DEPENDS "${_pch_bin}")
    endmacro()
elseif(CLANG)
else()
endif()

# ----------------------- subdirectories ------------------------
set(VOLT_CLIENT_CORE volt-client-core)

add_subdirectory(core)
add_subdirectory(console)

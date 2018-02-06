cmake_minimum_required(VERSION 3.4)

project(${VOLT_CLIENT_CORE})

include_directories(${VOLT_CORE_INCLUDE})

# --------------------------- sources ---------------------------
set(HEADERS
    include/configs/servers.h
    )

set(SOURCES
    )

set_source_group(${HEADERS})
set_source_group(${SOURCES})

# ------------------------ precompiled --------------------------
set(PRECOMPILED_HEADERS pch/stdafx.h pch/stdafx.cpp)
set_source_group(${PRECOMPILED_HEADERS})

get_filename_component(PRECOMPILED_DIR pch/ ABSOLUTE)
use_precompiled_header(${PRECOMPILED_DIR} ${SOURCES})

# ---------------------------------------------------------------
add_library(${PROJECT_NAME} STATIC ${PRECOMPILED_HEADERS} ${HEADERS} ${SOURCES})

# --------------------------- tests -----------------------------
set(VOLT_CLIENT_CORE_TEST test_${PROJECT_NAME})
add_test(NAME ${VOLT_CLIENT_CORE_TEST} COMMAND ${VOLT_CLIENT_CORE_TEST})

add_subdirectory(tests)

enable_testing()

cmake_minimum_required(VERSION 3.4)

project(${VOLT_UTILS})

# --------------------------- sources ---------------------------
set(HEADERS
    localization/locale.h
    memory/buffer.h
    memory/view.h
    network/transport_packet.h
    )

set(SOURCES
    localization/locale.cpp
    memory/buffer.cpp
    network/transport_packet.cpp
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
set(TEST_PROJECT test-${PROJECT_NAME})
add_test(NAME ${TEST_PROJECT} COMMAND ${TEST_PROJECT})

add_subdirectory(tests)

enable_testing()

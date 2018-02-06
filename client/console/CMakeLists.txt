cmake_minimum_required(VERSION 3.4)

project(volt-console)

# --------------------------- sources ---------------------------
set(HEADERS
    )

set(SOURCES
    src/main.cpp
    )

set_source_group(${HEADERS})
set_source_group(${SOURCES})

# ------------------------ precompiled --------------------------
set(PRECOMPILED_HEADERS pch/stdafx.h pch/stdafx.cpp)
set_source_group(${PRECOMPILED_HEADERS})

get_filename_component(PRECOMPILED_DIR pch/ ABSOLUTE)
use_precompiled_header(${PRECOMPILED_DIR} ${SOURCES})

# ---------------------------------------------------------------
add_executable(${PROJECT_NAME} ${PRECOMPILED_HEADERS} ${HEADERS} ${SOURCES})

target_link_libraries (${PROJECT_NAME}
    ${VOLT_CLIENT_CORE}
    ${Boost_LIBRARIES}
    ${FMT_LIBRARIES}
    ${VOLT_YAL_LIB}
    )

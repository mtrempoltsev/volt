project(${TEST_PROJECT})

# --------------------------- sources ---------------------------
set(HEADERS
    )

set(SOURCES
    memory/test_buffer.cpp
    network/test_transport_packet.cpp
    main.cpp
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

target_link_libraries(${PROJECT_NAME}
    ${VOLT_GTEST_LIBRARIES}
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${VOLT_UTILS}
    )

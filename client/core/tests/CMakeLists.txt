project(${VOLT_CORE_TEST_PROJECT})

set(SOURCES
    json/server_info_reader_test.cpp

    main.cpp)

add_executable(${VOLT_CORE_TEST_PROJECT} ${SOURCES})
set_target_properties(${VOLT_CORE_TEST_PROJECT} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ../src/stdafx.h)
cotire(${VOLT_CORE_TEST_PROJECT})

target_link_libraries(${VOLT_CORE_TEST_PROJECT}
    gtest
    yal
    fmt
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${OPENSSL_LIBRARIES}
    ${VOLT_CORE_PROJECT})

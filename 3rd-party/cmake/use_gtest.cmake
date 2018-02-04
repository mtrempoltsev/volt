﻿macro(use_gtest 3rd_parties_root)
    if(NOT TARGET googletest-distribution)
        set(BUILD_GTEST             ON  CACHE BOOL "Build gtest")
        set(BUILD_GMOCK             OFF CACHE BOOL "Build gmock")
        set(gtest_force_shared_crt  ON  CACHE BOOL "" FORCE)

        add_subdirectory(${3rd_parties_root}/google-test gtest)
        include_directories(${3rd_parties_root}/google-test/googletest/include)
        include_directories(${3rd_parties_root}/google-test/googlemock/include)
    endif()
endmacro()

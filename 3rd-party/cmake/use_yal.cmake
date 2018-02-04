﻿macro(use_yal 3rd_parties_root)
    if(NOT TARGET yal)
        set(YAL_BUILD_FMTLIB    OFF CACHE BOOL "Build Fmt" FORCE)
        set(YAL_BUILD_GTEST     OFF CACHE BOOL "Build Gtest" FORCE)
        set(YAL_BUILD_TESTS     OFF CACHE BOOL "Build YAL tests" FORCE)
        set(YAL_BUILD_EXAMPLES  OFF CACHE BOOL "Build YAL examples" FORCE)

        add_subdirectory("${3rd_parties_root}/yal" yal)
        include_directories("${3rd_parties_root}/yal/include")
    endif()
    if(Boost_FOUND)
        add_definitions(-DYAL_USES_BOOST)
    endif()
endmacro()

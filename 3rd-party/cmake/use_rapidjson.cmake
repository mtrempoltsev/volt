﻿macro(use_rapidjson 3rd_parties_root)
    if(NOT TARGET rapidjson)
        set(RAPIDJSON_BUILD_DOC                 OFF CACHE BOOL "Build rapidjson documentation." FORCE)
        set(RAPIDJSON_BUILD_EXAMPLES            OFF CACHE BOOL "Build rapidjson examples." FORCE)
        set(RAPIDJSON_BUILD_TESTS               OFF CACHE BOOL "Build rapidjson perftests and unittests." FORCE)
        set(RAPIDJSON_BUILD_THIRDPARTY_GTEST    OFF CACHE BOOL "Use gtest installation in `thirdparty/gtest` by default if available" FORCE)
        set(RAPIDJSON_BUILD_CXX11               ON  CACHE BOOL "Build rapidjson with C++11 (gcc/clang)" FORCE)
        set(RAPIDJSON_BUILD_ASAN                OFF CACHE BOOL "Build rapidjson with address sanitizer (gcc/clang)" FORCE)
        set(RAPIDJSON_BUILD_UBSAN               OFF CACHE BOOL "Build rapidjson with undefined behavior sanitizer (gcc/clang)" FORCE)
        set(RAPIDJSON_HAS_STDSTRING             ON  CACHE BOOL "Use std::string" FORCE)

        add_subdirectory("${3rd_parties_root}/rapidjson" rapidjson)
        include_directories("${3rd_parties_root}/rapidjson/include")
    endif()
endmacro()
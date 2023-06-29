cmake_minimum_required (VERSION 3.16)

option(SCIENCEPARSER_BUILD_TESTS "Build scienceParser tests" ON)
option(SCIENCEPARSER_BUILD_EXAMPLES "Build scienceParser examples" ON)
option(SCIENCEPARSER_BUILD_DOCS "Generate target for building docs" ON)

message(STATUS "SCIENCEPARSER_BUILD_TESTS: " ${SCIENCEPARSER_BUILD_TESTS})
message(STATUS "SCIENCEPARSER_BUILD_EXAMPLES: " ${SCIENCEPARSER_BUILD_EXAMPLES})
message(STATUS "SCIENCEPARSER_BUILD_DOCS: " ${SCIENCEPARSER_BUILD_DOCS})

project(scienceParser
        VERSION 1.0
        DESCRIPTION "ScienceParser C++ library built with CMake"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "Use build type: Release")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build (Debug, Release, etc.)" FORCE)
endif ()

# install and check deps
## =======================================\
include(${scienceParser_SOURCE_DIR}/cmake/CPM.cmake)
include(FindOpenSSL)

CPMAddPackage("https://github.com/open-source-parsers/jsoncpp.git#1.9.5")
CPMAddPackage("https://github.com/openssl/openssl.git#openssl-3.1.0")
CPMAddPackage("https://github.com/libcpr/cpr.git#1.9.3")

find_package(OpenSSL REQUIRED)
find_package(CPR REQUIRED)

## =======================================\

include_directories(include)
add_subdirectory(include)

add_subdirectory(src)

if (SCIENCEPARSER_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

if (SCIENCEPARSER_BUILD_TESTS)
    add_subdirectory(tests)
endif ()

if (SCIENCEPARSER_BUILD_DOCS)
    add_subdirectory(doc)
endif ()


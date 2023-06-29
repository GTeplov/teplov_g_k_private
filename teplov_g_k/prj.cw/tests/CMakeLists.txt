add_executable(test test.cpp)

add_library(doctest INTERFACE)
target_sources(
        doctest PUBLIC
        FILE_SET HEADERS
        FILES doctest.h)

target_link_libraries(test scienceParser doctest)
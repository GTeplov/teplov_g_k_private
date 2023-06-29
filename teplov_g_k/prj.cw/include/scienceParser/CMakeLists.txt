add_library(${PROJECT_NAME} INTERFACE)
target_sources(
        ${PROJECT_NAME} PUBLIC
        FILE_SET HEADERS
        FILES Articles.hpp API.hpp CrossRefAPI.hpp)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${PROJECT_NAME} INTERFACE jsoncpp_lib)
target_link_libraries(${PROJECT_NAME} INTERFACE cpr::cpr)
add_executable(${PROJECT_NAME}-test-app main.cpp)
target_link_libraries(${PROJECT_NAME}-test-app scienceParser)

# Debug
## =======================================\
install(TARGETS
        ${PROJECT_NAME}-test-app
        CONFIGURATIONS Debug
        RUNTIME DESTINATION .)

install(TARGETS
        cpr
        CONFIGURATIONS Debug
        RUNTIME DESTINATION .)

install(TARGETS
        libcurl
        CONFIGURATIONS Debug
        RUNTIME DESTINATION .)

install(TARGETS
        jsoncpp_lib
        CONFIGURATIONS Debug
        RUNTIME DESTINATION .)

## =======================================\

# Release
## =======================================\
install(TARGETS
        cpr
        CONFIGURATIONS Release
        RUNTIME DESTINATION .)

install(TARGETS
            ${PROJECT_NAME}-test-app
        CONFIGURATIONS Release
        RUNTIME DESTINATION .)

install(TARGETS
        libcurl
        CONFIGURATIONS Release
        RUNTIME DESTINATION .)

install(TARGETS
        jsoncpp_lib
        CONFIGURATIONS Release
        RUNTIME DESTINATION .)

## =======================================\


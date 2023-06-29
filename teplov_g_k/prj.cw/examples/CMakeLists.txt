add_executable(${PROJECT_NAME}-getArticleExample getArticleExample.cpp)
target_link_libraries(${PROJECT_NAME}-getArticleExample ${PROJECT_NAME})

install(TARGETS
        ${PROJECT_NAME}-getArticleExample
        CONFIGURATIONS Debug
        RUNTIME DESTINATION .)

install(TARGETS
        ${PROJECT_NAME}-getArticleExample
        CONFIGURATIONS Release
        RUNTIME DESTINATION .)



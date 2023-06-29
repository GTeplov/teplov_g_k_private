if (SCIENCEPARSER_BUILD_DOCS)
    find_package(Doxygen REQUIRED)

    set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})

    # Doxygen configuration
    set(scienceParser_DOCS_OUTPUT_LANGUAGE "Russian" CACHE STRING "Documentation language")
    set(scienceParser_DOXYGEN_INPUT ${scienceParser_SOURCE_DIR}/include/scienceParser/)

    # Doxygen format for list of directories
    list(JOIN scienceParser_DOXYGEN_INPUT " " scienceParser_DOXYGEN_INPUT)

    configure_file(
            Doxyfile.in
            ${scienceParser_BINARY_DIR}/Doxyfile
    )

    add_custom_target(
            scienceParser-docs ALL
            ${DOXYGEN_EXECUTABLE} ${scienceParser_BINARY_DIR}/Doxyfile
            # WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Target to generate docs" VERBATIM)

    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS Doxyfile.in)

    install(DIRECTORY ${DOXYGEN_OUTPUT_DIR}/doc DESTINATION ${CMAKE_INSTALL_PREFIX})
endif ()
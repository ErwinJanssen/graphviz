if (GD_FOUND)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${TOP_SOURCE_DIR}/windows/getopt
    ${GD_INCLUDE_DIRS}
)

add_executable(diffimg
    # Source files
    diffimg.c
)

target_link_libraries(diffimg
    ${GD_LIBRARIES}
)

if(NOT HAVE_GETOPT_H)
    target_link_libraries(diffimg getopt)
endif(NOT HAVE_GETOPT_H)

install(
    TARGETS diffimg
    RUNTIME DESTINATION ${BINARY_INSTALL_DIR}
    LIBRARY DESTINATION ${PLUGIN_INSTALL_DIR}
    ARCHIVE DESTINATION ${LIBRARY_INSTALL_DIR}
)

# Include DLLs with this library on Windows
if (WIN32)
    install(
        FILES
            ${GD_RUNTIME_LIBRARIES}
        DESTINATION ${BINARY_INSTALL_DIR}
    )
endif()

install(
    FILES diffimg.1
    DESTINATION ${MAN_INSTALL_DIR}
)

endif (GD_FOUND)

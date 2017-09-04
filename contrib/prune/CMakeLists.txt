include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${TOP_SOURCE_DIR}/windows/getopt
    ${GRAPHVIZ_LIB_DIR}/cdt
    ${GRAPHVIZ_LIB_DIR}/cgraph
    ${GRAPHVIZ_LIB_DIR}/ingraphs
)

add_executable(prune
    # Header files
    generic_list.h

    # Source files
    generic_list.c
    prune.c
)

target_link_libraries(prune
    cdt
    cgraph
    ingraphs
)

if(NOT HAVE_GETOPT_H)
    target_link_libraries(prune getopt)
endif(NOT HAVE_GETOPT_H)

install(
    TARGETS prune
    RUNTIME DESTINATION ${BINARY_INSTALL_DIR}
    LIBRARY DESTINATION ${PLUGIN_INSTALL_DIR}
    ARCHIVE DESTINATION ${LIBRARY_INSTALL_DIR}
)

install(
    FILES prune.1
    DESTINATION ${MAN_INSTALL_DIR}
)

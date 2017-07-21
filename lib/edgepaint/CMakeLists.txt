include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GRAPHVIZ_LIB_DIR}/cdt
    ${GRAPHVIZ_LIB_DIR}/cgraph
    ${GRAPHVIZ_LIB_DIR}/common
    ${GRAPHVIZ_LIB_DIR}/gvc
    ${GRAPHVIZ_LIB_DIR}/pathplan
    ${GRAPHVIZ_LIB_DIR}/sfdpgen
    ${GRAPHVIZ_LIB_DIR}/sparse
)

add_library(libedgepaint
    # Header files
    edge_distinct_coloring.h
    furtherest_point.h
    intersection.h
    lab.h
    node_distinct_coloring.h

    # Source files
    edge_distinct_coloring.c
    furtherest_point.c
    intersection.c
    lab.c
    node_distinct_coloring.c
)

add_definitions(-DLAB_GAMUT_EXPORTS)

add_library(lab_gamut SHARED
    # Header files
    lab_gamut.h

    # Source files
    lab_gamut.c

    # Link definition file for Windows
    lab_gamut.def
)

# Installation location of library files
install(
    TARGETS lab_gamut
    RUNTIME DESTINATION ${BINARY_INSTALL_DIR}
    LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR}
    ARCHIVE DESTINATION ${LIBRARY_INSTALL_DIR}
)

# Specify man pages to be installed
install(
    FILES lab_gamut.3
    DESTINATION ${MAN_INSTALL_DIR}
)

# Specify library version and soversion
set_target_properties(lab_gamut PROPERTIES
    VERSION 1.0.0
    SOVERSION 1
)

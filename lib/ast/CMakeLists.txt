include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GRAPHVIZ_LIB_DIR}/sfio
    ${TOP_BINARY_DIR}/lib/sfio
)

add_library(ast STATIC
    # Header files
    align.h
    ast.h
    compat_unistd.h
    error.h
    hashkey.h
    sfstr.h

    # Source files
    chresc.c
    chrtoi.c
    error.c
    fmtbuf.c
    fmtesc.c
    pathaccess.c
    pathbin.c
    pathcanon.c
    pathcat.c
    pathexists.c
    pathfind.c
    pathgetlink.c
    pathpath.c
    strcopy.c
    stresc.c
    strmatch.c
    strton.c
)

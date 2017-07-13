include_directories(
    ${GRAPHVIZ_LIB_DIR}/sfio
    ${TOP_BINARY_DIR}/lib/sfio
)

add_library(sfiof STATIC
    # Source files
    _sfclrerr.c
    _sfdlen.c
    _sfeof.c
    _sferror.c
    _sffileno.c
    _sfgetc.c
    _sfllen.c
    _sfputc.c
    _sfputd.c
    _sfputl.c
    _sfputm.c
    _sfputu.c
    _sfslen.c
    _sfstacked.c
    _sfulen.c
    _sfvalue.c
)

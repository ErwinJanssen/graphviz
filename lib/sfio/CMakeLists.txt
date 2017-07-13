list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/features")
include(sfio_checks)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/features/sfio_features.in
    ${CMAKE_CURRENT_BINARY_DIR}/FEATURE/sfio
    @ONLY
)

add_subdirectory(Sfio_f)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${GRAPHVIZ_LIB_DIR}/ast
)

add_library(sfio STATIC
    # Header files
    sfhdr.h
    sfio.h
    sfio_t.h
    vthread.h

    # Source files
    sfclose.c
    sfclrlock.c
    sfcvt.c
    sfdisc.c
    sfdlen.c
    sfexcept.c
    sfexit.c
    sfextern.c
    sffcvt.c
    sffilbuf.c
    sfflsbuf.c
    sfgetd.c
    sfgetl.c
    sfgetm.c
    sfgetr.c
    sfgetu.c
    sfllen.c
    sfmode.c
    sfmove.c
    sfmutex.c
    sfnew.c
    sfnotify.c
    sfnputc.c
    sfopen.c
    sfpkrd.c
    sfpoll.c
    sfpool.c
    sfpopen.c
    sfprintf.c
    sfprints.c
    sfpurge.c
    sfputd.c
    sfputl.c
    sfputm.c
    sfputr.c
    sfputu.c
    sfraise.c
    sfrd.c
    sfread.c
    sfreserve.c
    sfresize.c
    sfscanf.c
    sfseek.c
    sfset.c
    sfsetbuf.c
    sfsetfd.c
    sfsize.c
    sfsk.c
    sfstack.c
    sfstrtod.c
    sfswap.c
    sfsync.c
    sftable.c
    sftell.c
    sftmp.c
    sfungetc.c
    sfvprintf.c
    sfvscanf.c
    sfwr.c
    sfwrite.c
)

target_link_libraries(sfio sfiof)

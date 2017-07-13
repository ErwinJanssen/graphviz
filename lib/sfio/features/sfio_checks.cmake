# These checks are ported from features/sfio and are used in sfio only
include(CheckCSourceRuns)

# file not removable if still opened
check_c_source_runs(
    "#include	<sys/time.h>
    extern int creat(char*, int);
    extern int unlink(char*);
    extern int write(int, char*, int);
    main()
    {
        int fw, fr;
        char file[128];
        sprintf(file,\"/tmp/iffe%lu\",(unsigned long)time(0));
        if((fw = creat(file,0666)) < 0)
            return 0;
        if((fr = open(file,0)) < 0 )
            return 0;
        if(unlink(file) < 0)
            return 0;
        if(write(fw,\"0123456789\",11) != 11 )
            return 0;
        if(read(fr,file,11) != 11)
            return 0;
        if(strcmp(file,\"0123456789\") != 0)
            return 0;
        return 1;
    }"
    _tmp_rmfail
)

# st_blksize is a field in struct stat
check_c_source_runs(
    "#include <sys/types.h>
    #include <sys/stat.h>
    main () {
        struct stat sb;
        sb.st_blksize = 0;
        return 0;
    }"
    _stat_blksize
)

# open() has a vararg prototype
check_c_source_runs(
  "#include	<sys/types.h>
  #include	<errno.h>
  #include	<ctype.h>
  #include	<fcntl.h>

  extern int open(const char*,int,...);

  main()
  {
      open(\"file\",0);
      open(\"file\",0,1);
  }"
  _proto_open
)

# fd is first arg to poll()
check_c_source_runs(
    "#include <poll.h>

    extern int      pipe(int*);

    main()
    {
        int rw[2];
        struct pollfd fd;
        if (pipe(rw) < 0) return 1;
        fd.fd = rw[0];
        fd.events = POLLIN;
        fd.revents = 0;
        return poll(&fd, 1, 0) < 0;
    }"
    _lib_poll_fd_1
)

# fd is second arg to poll()
check_c_source_runs(
    "#include <poll.h>

    extern int      pipe(int*);

    main()
    {
        int rw[2];
        struct pollfd fd;
        if (pipe(rw) < 0) return 1;
        fd.fd = rw[0];
        fd.events = POLLIN;
        fd.revents = 0;
        return poll(1, &fd, 0) < 0;
    }"
    _lib_poll_fd_2
)

# ioctl(I_PEEK) works
check_c_source_runs(
    "#include <sys/types.h>
    #include <stropts.h>
    main()
    {
        struct strpeek  pbuf;
        pbuf.flags = 0;
        pbuf.ctlbuf.maxlen = pbuf.databuf.maxlen =
        pbuf.ctlbuf.len = pbuf.databuf.len = 0;
        pbuf.ctlbuf.buf = pbuf.databuf.buf = 0;
        ioctl(0,I_PEEK,&pbuf);
        return 0;
    }"
    _stream_peek
)

# recv(MSG_PEEK) works
check_c_source_runs(
    "# recv(MSG_PEEK) works
    #include <sys/types.h>
    #include <sys/socket.h>
    main()
    {
        char buf[128];
        recv(0,buf,sizeof(buf),MSG_PEEK);
        return 0;
    }"
    _socket_peek
)

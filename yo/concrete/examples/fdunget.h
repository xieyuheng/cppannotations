    #include <unistd.h>
    #include <streambuf>
    #include <ios>
    #include <algorithm>
    #include <cstring>

//CLASS
    class FdUnget: public std::streambuf
    {
        int     d_fd;
        size_t  d_bufsize;
        size_t  d_reserved;
        char   *d_buffer;
        char   *d_base;
        public:
            FdUnget(int fd, size_t bufsz, size_t unget);
            virtual ~FdUnget();
        private:
            int underflow();
    };
//=
//CONS
    FdUnget::FdUnget(int fd, size_t bufsz, size_t unget)
    :
        d_fd(fd),
        d_reserved(unget)
    {
        size_t allocate =
                bufsz > d_reserved ?
                    bufsz
                :
                    d_reserved + 1;

        d_buffer = new char[allocate];

        d_base = d_buffer + d_reserved;
        setg(d_base, d_base, d_base);

        d_bufsize = allocate - d_reserved;
    }
//=
//DESTR
    inline FdUnget::~FdUnget()
    {
        delete[] d_buffer;
    }
//=
//UNDERFLOW
    int FdUnget::underflow()
    {
        size_t ungetsize = gptr() - eback();
        size_t move = std::min(ungetsize, d_reserved);

        memcpy(d_base - move, egptr() - move, move);

        int nread = read(d_fd, d_base, d_bufsize);
        if (nread <= 0)       // none read -> return EOF
            return EOF;

        setg(d_base - move, d_base, d_base + nread);

        return static_cast<unsigned char>(*gptr());
    }
//=

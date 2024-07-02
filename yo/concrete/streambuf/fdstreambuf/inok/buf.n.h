#include <unistd.h>
#include <streambuf>
#include <ios>

class fdstreambuf: public std::streambuf
{
    public:
        fdstreambuf(int fd, size_t bufsize, std::ios::openmode mode =
                                std::ios::in | std::ios::out)
        :
            fd(fd),
            bufsize(bufsize),
            buffer(new char[bufsize])
        {
            if (mode & std::ios::in)
                setg(buffer, buffer + bufsize, buffer + bufsize);
        }

        ~fdstreambuf()
        {
            delete buffer;
        }

        int underflow()             // inspects the character
        {
            if (gptr() < egptr())
                return static_cast<unsigned char>(*gptr());
                                    // return next char waiting in the buffer

            int
                nread = read(fd, buffer, bufsize);

            if (nread <= 0)       // none read ->
                return EOF;

            setg(buffer, buffer, buffer + nread);
            return static_cast<unsigned char>(*gptr());
        }

    private:
        int         fd;
        size_t    bufsize;
        char*       buffer;
};

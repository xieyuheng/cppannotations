#include <unistd.h>
#include <streambuf>
#include <ios>
#include <algorithm>

using namespace std;

class fdstreambuf: public std::streambuf
{
    public:
        fdstreambuf(int fd, size_t bufsize, size_t minimum,
                    std::ios::openmode mode = std::ios::in | std::ios::out)
        :
            fd(fd),
            bufsize(bufsize),
            minimum(minimum),
            buffer(new char[bufsize])
        {
/*
    initialize buffer from minimum position to beyond, set
    gptr() to beyond, so the buffer is filled immediately

    Assume bufsize - minimum > minimum
*/
            if (mode & std::ios::in)
                setg(buffer + minimum, buffer + bufsize, buffer + bufsize);
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

/*
    Now that the buffer is refilled, what do we have?
    buffer      eback()             gptr() == egptr()
    ^           ^                   ^
    -------------------------------
            n           m <= bufsize - minimum

    n characters at chars before gptr() are moved left,
    eback() is moved left over n
    filling starts are buffer + minimum
*/

            size_t
                n2move = min(minimum, (size_t)(gptr() - eback()));

            memcpy(buffer, egptr() - n2move, n2move);

/*
    Read chars to the area beyond the unget-buffer
*/
            int
                nread = read(fd, buffer + minimum, bufsize - minimum);

            if (nread <= 0)       // none read ->
                return EOF;

            setg(buffer + minimum - n2move,
                 buffer + minimum,
                 buffer + minimum + nread);

            return static_cast<unsigned char>(*gptr());
        }

    private:
        int         fd;
        size_t    bufsize;
        size_t    minimum;
        char*       buffer;
};

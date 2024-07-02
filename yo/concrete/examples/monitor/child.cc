    #include "child.h"
    #include <iostream>
    #include <string>
    #include <cstdlib>

    using namespace std;

//CHILD
    void Child::childRedirections()
    {
        d_in.readFrom(STDIN_FILENO);
        d_out.writtenBy(STDOUT_FILENO);
    }
//=
//PARENT
    void Child::parentRedirections()
    {
        d_parentReadFd = d_out.readOnly();
        d_parentWriteFd = d_in.writeOnly();
    }
//=
//PROCESS
    void Child::childProcess()
    {
        Selector    selector;
        size_t    message = 0;

        selector.addReadFd(STDIN_FILENO);
        selector.setAlarm(5);

        while (true)
        {
            try
            {
                if (!selector.wait())       // timeout
                    cout << "Child " << d_nr << ": standing by\n";
                else
                {
                    string  line;
                    getline(cin, line);
                    cout << "Child " << d_nr << ":" << ++message << ": " <<
                                                        line << '\n';
                }
            }
            catch (...)
            {
                    cout << "Child " << d_nr << ":" << ++message << ": " <<
                                "select() failed" << '\n';
            }
        }
        exit(0);
    }
//=

//CHILDDES
    Child::~Child()
    {
        if (pid())
        {
            cout << "Killing process " << pid() << "\n";
            kill(pid(), SIGTERM);
            int status;
            wait(&status);
        }
    }
//=

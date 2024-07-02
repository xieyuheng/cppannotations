    #include <iostream>
    #include "sumvector.h"

    using namespace std;

    int main()
    {
        int
            x[] = {1, 2};
        double
            y[] = {1.1, 2.2};

        cout << sumVector(x, 2) << '\n'     // first instantiation
            << sumVector(y, 2) << '\n';     // second instantiation

        unsigned long                       // third instantiation
            (*pf)(unsigned long *, size_t) = sumVector;
    }
    /*
        Generated output:

        3
        3.3
    */

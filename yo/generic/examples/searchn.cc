    #include <algorithm>
    #include <iostream>
    #include <iterator>
    using namespace std;

    bool eqInt(int i1, int i2)
    {
        return abs(i1) == abs(i2);
    }
    int main()
    {
        int range1[] =  {-2, -4, -4, -6, -8, 2, 4, 4, 6, 8};

        copy
        (
            search_n(range1, range1 + 8, 2, 4),
            range1 + 8,
            ostream_iterator<int>(cout, " ")
        );
        cout << '\n';

        copy
        (
            search_n(range1, range1 + 8, 2, 4, eqInt),
            range1 + 8,
            ostream_iterator<int>(cout, " ")
        );
        cout << '\n';
    }
    /*
        Displays:
            4 4
            -4 -4 -6 -8 2 4 4
    */

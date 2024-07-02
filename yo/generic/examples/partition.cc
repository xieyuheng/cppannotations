    #include <algorithm>
    #include <iostream>
    #include <string>
    #include <iterator>
    using namespace std;

    class LessThan
    {
        int d_x;
        public:
            LessThan(int x)
            :
                d_x(x)
            {}
            bool operator()(int value) const
            {
                return value <= d_x;
            }
    };
    int main()
    {
        int ia[] = {1, 3, 5, 7, 9, 10, 2, 8, 6, 4};
        int *split;

        split = partition(ia, ia + 10, LessThan{ ia[9] });
        cout << "Last element <= 4 is ia[" << split - ia - 1 << "]\n";

        copy(ia, ia + 10, ostream_iterator<int>{ cout, " " });
        cout << '\n';
    }
    /*
        Displays:
            Last element <= 4 is ia[3]
            1 3 4 2 9 10 7 8 6 5
    */

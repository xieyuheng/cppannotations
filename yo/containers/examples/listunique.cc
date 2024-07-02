    #include <iostream>
    #include <string>
    #include <list>
    using namespace std;
                            // see the merge() example
    void showlist(list<string> &target)
    {
        for
        (
            list<string>::iterator from = target.begin();
            from != target.end();
            ++from
        )
            cout << *from << " ";

        cout << '\n';
    }


    int main()
    {
        string
            array[] =
            {
                "charlie",
                "alpha",
                "bravo",
                "alpha"
            };

        list<string>
            target
            (
                array, array + sizeof(array)
                / sizeof(string)
            );

        cout << "Initially we have:\n";
        showlist(target);

        target.sort();
        cout << "After sort() we have:\n";
        showlist(target);

        target.unique();
        cout << "After unique() we have:\n";
        showlist(target);
    }
    /*
        Generated output:

        Initially we have:
        charlie alpha bravo alpha
        After sort() we have:
        alpha alpha bravo charlie
        After unique() we have:
        alpha bravo charlie
    */

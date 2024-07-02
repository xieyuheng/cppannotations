    #include <iostream>
    #include <fstream>
    #include <string>
    #include <climits>
    using namespace std;

    void err(char const *msg)
    {
        cout << msg << '\n';
    }

    void err(char const *msg, long value)
    {
        cout << msg << value << '\n';
    }

    void read(fstream &index, fstream &strings)
    {
        int idx;

        if (!(cin >> idx))                          // read index
        {
            cin.clear();                            // allow reading again
            cin.ignore(INT_MAX, '\n');              // skip the line
            return err("line number expected");
        }

        index.seekg(idx * sizeof(long));            // go to index-offset

        long offset;

        if
        (
            !index.read                             // read the line-offset
            (
                reinterpret_cast<char *>(&offset),
                sizeof(long)
            )
        )
            return err("no offset for line", idx);

        if (!strings.seekg(offset))                 // go to the line's offset
            return err("can't get string offset ", offset);

        string line;

        if (!getline(strings, line))                // read the line
            return err("no line at ", offset);

        cout << "Got line: " << line << '\n';       // show the line
    }

    void write(fstream &index, fstream &strings)
    {
        string line;

        if (!getline(cin, line))                  // read the line
            return err("line missing");

        strings.seekp(0, ios::end);               // to strings
        index.seekp(0, ios::end);                 // to index

        long offset = strings.tellp();

        if
        (
            !index.write                          // write the offset to index
            (
                reinterpret_cast<char *>(&offset),
                sizeof(long)
            )
        )
            return err("Writing failed to index: ", offset);

        if (!(strings << line << '\n'))           // write the line itself
            return err("Writing to `strings' failed");
                                                  // confirm writing the line
        cout << "Write at offset " << offset << " line: " << line << '\n';
    }

    int main()
    {
        fstream index("index", ios::trunc | ios::in | ios::out);
        fstream strings("strings", ios::trunc | ios::in | ios::out);

        cout << "enter `r <number>' to read line <number> or "
                                    "w <line>' to write a line\n"
                "or enter `q' to quit.\n";

        while (true)
        {
            cout << "r <nr>, w <line>, q ? ";       // show prompt

            index.clear();
            strings.clear();

            string cmd;
            cin >> cmd;                             // read cmd

            if (cmd == "q")                         // process the cmd.
                return 0;

            if (cmd == "r")
                read(index, strings);
            else if (cmd == "w")
                write(index, strings);
            else if (cin.eof())
            {
                cout << "\n"
                        "Unexpected end-of-file\n";
                return 1;
            }
            else
                cout << "Unknown command: " << cmd << '\n';
        }
    }

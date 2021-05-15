#include <vector>
#include <fstream>
#include <cstdlib>
#include <iostream>

int drawDiceFaces(std::vector<short> values, const char* seperator) {
    using namespace std;
    
    // Counts from 0. -1 would mean no faces
    short _inputs = values.size() - 1;

    // Check for invalid faces
    for (short face : values)
        if (face <= 0 || face > 6) return 1;

    // Top
    for (short i = 0; i != values.size(); i++) {
        cout << "+-------+";
        if (i < _inputs)
            cout << seperator;
    }
    cout << endl;
    
    // First row
    for (short i = 0; i != values.size(); i++) {
        short _value = values[i];
        if (_value >= 2 && _value <= 3)
            cout << "|     O |";
        else if (_value >= 4)
            cout << "| O   O |";
        else
            cout << "|       |";
        if (i < _inputs)
            cout << seperator;
    }
    cout << endl;
    
    // Second row
    for (short i = 0; i != values.size(); i++) {
        short _value = values[i];
        if (_value % 2 == 1)
            cout << "|   O   |";
        else if (_value == 6)
            cout << "| O   O |";
        else
            cout << "|       |";
        if (i < _inputs)
            cout << seperator;
    }
    cout << endl;
    
    // Third row
    for (short i = 0; i != values.size(); i++) {
        short _value = values[i];
        if (_value >= 2 && _value <= 3)
            cout << "| O     |";
        else if (_value >= 4)
            cout << "| O   O |";
        else
            cout << "|       |";
        if (i < _inputs)
            cout << seperator;
    }
    cout << endl;
    
    // Bottom
    for (short i = 0; i != values.size(); i++) {
        cout << "+-------+";
        if (i < _inputs)
            cout << seperator;
    }
    cout << endl;

    return 0;
}

short getFace() {
    using namespace std;
    
    // Declare the output variable
    short _output = -1;

    // Get it's size (used for reading the buffer)
    size_t _size = sizeof(_output);

    // Open /dev/_urandom for read
    ifstream _urandom("/dev/urandom", ios::in|ios::binary);

    // Check if the stream is open
    if (_urandom) {
        _urandom.read(reinterpret_cast<char *>(&_output), _size);
        // Check if the read succeded
        if (_urandom) {
            _output %= 6;
            _output = abs(_output);
        } else {
            cerr << "Failed to read /dev/_urandom! 0x1" << endl;
            _output = -1;
        }
        _urandom.close();
    } else {
        cerr << "Failed to open /dev/_urandom! 0x2" << endl;
    }
    
    // Add one
    _output++;

    return _output;
}

int main(int argc, const char* argv[]) {
    using namespace std;

    if (argc < 2) {
        cerr << "Provide at least one number as a parameter" << endl;
        return 1;
    }
    
    short _count = atoi(argv[1]);
    if (_count == 0) {
        cerr << "The parameter's value was not a valid number" << endl;
        return 1;
    }

    vector<short> values = vector<short>();
    for (short i = 0; i < _count; i++)
        values.push_back(getFace());
    
    // Echo our random numbers back
    cout << "Numbers ";
    for (short i = 0; i != values.size(); i++) {
        if (i > 0)
            if (i < values.size() - 1)
                cout << ", ";
            else
                cout << " and ";
        cout << values[i];
    }
    cout << " have been rolled!" << endl << endl;

    return drawDiceFaces(values, " - ");
}
#include <iostream>
#include <fstream>

int drawDiceFace(short * face) {
    using namespace std;
    
    // Check for invalid faces
    if (*face <= 0 || *face > 6) return 1;

    // Top
    cout << "+-------+" << endl;
    
    // First row
    if (*face >= 2 && *face <= 3)
        cout << "|     O |" << endl;
    else if (*face >= 4)
        cout << "| O   O |" << endl;
    else
        cout << "|       |" << endl;
    
    // Second row
    if (*face % 2 == 1)
        cout << "|   O   |" << endl;
    else if (*face == 6)
        cout << "| O   O |" << endl;
    else
        cout << "|       |" << endl;
    
    // Third row
    if (*face >= 2 && *face <= 3)
        cout << "| O     |" << endl;
    else if (*face >= 4)
        cout << "| O   O |" << endl;
    else
        cout << "|       |" << endl;
    
    // Bottom
    cout << "+-------+" << endl;

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

int main() {
    using namespace std;

    short _face = getFace();
    
    // Echo our random number
    if (_face > 0)
        cout << "Number " << _face << " has been rolled!" << endl << endl;

    // Draw the face
    return drawDiceFace(&_face);
}
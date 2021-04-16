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

int main() {
    using namespace std;

    // Declare the output variable
    short face = -1;

    // Get it's size (used for reading the buffer)
    size_t size = sizeof(face);

    // Open /dev/urandom for read
    ifstream urandom("/dev/urandom", ios::in|ios::binary);

    // Check if the stream is open
    if (urandom) {
        urandom.read(reinterpret_cast<char *>(&face), size);
        // Check if the read succeded
        if (urandom) {
            face %= 6;
            face = abs(face);
        } else {
            cerr << "Failed to read /dev/urandom!";
            face = -1;
        }
        urandom.close();
    } else {
        cerr << "Failed to open /dev/urandom!";
    }
    
    // Add one
    face++;
    
    // Echo our random number
    cout << "Number " << face << " has been rolled!" << endl << endl;

    // Draw the face
    return drawDiceFace(&face);
}
// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 4) // If the argument count is not correct...
    { // ... then disaply an error message and exit.
        cout << "Error: Must supply exactly 3 arguments to the program! (" << (argc - 1) << " were supplied)";
        return 0;
    }

    // Get the program arguments as strings.
    string dict_filename = (string)argv[1];
    string first_word = (string)argv[2];
    string last_word = (string)argv[3];

    int first_len = first_word.length();
    int last_len = last_word.length();
}

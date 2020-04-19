// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

// A helper function that converts every character in a string to their respective lowercase values,
// and therefore outputs the entire string in lowercase.
string stringToUpper(const string s) {
	string tmp = s;
	for (int i = 0; i < s.length(); i++)
		tmp[i] = toupper(s[i]);
	return tmp;
}

int main(int argc, char* argv[])
{
    if (argc != 4) // If the argument count is not correct...
    { // ... then disaply an error message and exit.
        cout << "Error: Must supply exactly 3 arguments to the program! (" << (argc - 1) << " were supplied)";
        return 0; // exit the program
    }

    // Get the first and last words from the program args as uppercase words.
    string dict_filename = (string)argv[1];
    string first_word = stringToUpper((string)argv[2]);
    string last_word = stringToUpper((string)argv[3]);

	if (first_word.length() != last_word.length()) // If the first word and last word have a different number of letters
	{ // then display an error message and exit.
		cout << "Error: The second and third arguments must be strings of equal length!";
		return 0; // exit the program
	}

	int word_len = first_word.length();

	cout << first_word << endl;
	cout << last_word << endl;
}

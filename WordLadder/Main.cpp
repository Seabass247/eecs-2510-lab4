// Main.cpp
// By Sebastian Hamel
// For EECS 2510, Spring 2020
// Written 4/20/2020
// Contains the main function which is the entry point to this program.  Parses arguments passed to the program,
// and if the arguments are in a valid format, find the shortest word latter corresponding to the conditions
// from the arguments.

#include <iostream>
#include "WordLadder.h"
using namespace std;

// A helper function that converts every character in a string to their respective lowercase values,
// and therefore outputs the entire string in lowercase.
string stringToUpper(const string s) {
	string tmp = s;
	for (int i = 0; i < s.length(); i++)
		tmp[i] = toupper(s[i]);
	return tmp;
}

// The entry point to the program. Consumes arguments passed to WordLadder.exe and if the correct number of
// arguments are supplied, parse them into a dictionary file name, the first word string, last word string
// respectively.  Then, with these paramaters, find the shortest word ladder between the START and END words
// and ouput the result.
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

	// Create a new word ladder, get the shortest word ladder, and display the result
	// whether such a word ladder exists or not.
	WordLadder* wordLadder = new WordLadder(dict_filename, first_word.length());
	vector<string> resultSequence = wordLadder->getMinLadder(first_word, last_word);
	wordLadder->displayResult(resultSequence);
}

// WordLadder.cpp
// By Sebastian Hamel
// For EECS 2510, Spring 2020
// Written 4/23/2020
// Here is the implementation of the WordLadder class and the definitions of WordLadder's methods.
// Creates a word ladder by reading a dictionary file to create a set of known words, then uses the
// Breadth-first Search (BFS) algorithm to find the shortest path from some START word to some END end,
// with a method to neatly display the word ladder (if there is one) and the number of steps taken from 
// START to END, by taking the resulting sequence and bactracking, iterating through the sequence 
// in REVERSE to display to words in the correct order, because the BFS algorithm returns a reversed 
// sequence by backtracking through predecessors.

#include "WordLadder.h"
#include <iostream>
#include <fstream>
#include <list>

// The constructor. Creates the word ladder, populating the lexicon string set with the words read in 
// from a specified file, only keeping the words with the specified length.  This is assuming that
// the dictionary file exists and can be opened, otherwise we cannot go further, display an error
// and exit the program.
WordLadder::WordLadder(string lexiconFileName, int len)
{
	ifstream file;
	file.open(lexiconFileName); // open the dictionary file so it can be read into words
	if (!file) // If the specified file cannot be opened, display an error message and exit
	{
		cout << "Error: Dictionary file could not be opened!" << endl;
		exit(0);
	}
	// Read in words from the dictionary, and only keep the words that match
	// the specified length
	std::string word;
	while (file >> word) // Insert all the appropriate-length words into the lexicon set
	{
		if (word.length() != len) // Skip over words with the incorrect length
			continue;
		lexicon.insert(word); // Add the word to our lexicon
	}
}

// Returns a minimum-length word ladder from start to end. If multiple minimum-length
// word ladders exist, no guarantee is made regarding which one is returned. If no word
// ladder exists, this method returns an empty list. Uses a breadth-first search.
vector<string> WordLadder::getMinLadder(string start, string end)
{
	if (!isWord(start)) // if the START word is not in the dictionary, we cannot proceed to make a word ladder...
		return vector<string>(); // ...return an empty word ladder (there will be no solution)

	vector<string> ladder; // start with an empty ladder,
	vector<string> wordsSeen; // list of words seen,
	vector<string> wordPredecessors; // and list of every word's predecessor

	list<string> queue;
	queue.push_back(start); // Start with the queue containing the first word in the ladder
	wordsSeen.push_back(start); // Mark the first word as seen
	wordPredecessors.push_back(""); // Set the first word's predecessor to "" (nothing)

	while (!queue.empty()) // BFS will keep going as long as there's items in the queue
	{
		string QFront = queue.front(); // Get first item from the queue...
		queue.pop_front(); // ...and remove it

		set<string> neighbors = getNeighbors(QFront); // Get a list of QFront's neighbors.
		for (std::set<string>::iterator it = neighbors.begin(); it != neighbors.end(); ++it)
			// For each neighbor S
		{
			string S = *it;
			if (findInVector(wordsSeen, S) == -1) 
				// If we haven't seen S before
			{
				if (S == end) // IF S is the END word of the ladder
				{
					wordsSeen.push_back(S); // Add S to the list of words we've seen
					wordPredecessors.push_back(QFront); // Add QFront to the list of predecessors 
					
					string currentWord = S; // Start from S
					while (currentWord != "") // Iteratively travel back to the START word from S, following precessors.
					{
						ladder.push_back(currentWord); // Add the current word to the ladder list
						// Advance currentWord to it's predecessor for the next loop
						currentWord = wordPredecessors.at(findInVector(wordsSeen, currentWord));
					}
					
					return ladder; // the BFS algorithm is finished, we're at the END word, so the ladder is complete; return it
				}
				else
				{
					wordsSeen.push_back(S); // Add S to the list of words we've seen
					wordPredecessors.push_back(QFront); // Add QFront to the list of predecessors 
					queue.push_back(S);
				}
			}

		} // end for
	} // end while
	return vector<string>(); // if we got here, we never took the return in the above for loop, thus there is not a valid word ladder,
							 // so return the empty vector.
}

// Returns the location within the vector of the given string (value of the specified string's index in the vector); returns -1 if not found
// by means of iterating through the entire vector, comaparing the string to the current string at the current iteration until
// said strings are equal, otherwise if the return wasn't taken, the loop ends and we return -1, meaning the string was not found.
int WordLadder::findInVector(vector<string> vec, string str)
{
	int location = -1; // location starts at -1 so that in the for loop it begins counting at 0.
	for (std::vector<string>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		location++; // Move the location of the given string over 1, since the string hasn't been found yet
		if (*it == str) // If the value at the current iteration equals the string we're looking for
			return location; // return the location of said string in the vector
	}
	// If we got here, we never took the return, thus the string was not found in the vector, represented by -1
	return -1;
}

// Checks to see if the given string is a word, by means of iterating through the entire set, comparing said string to 
// the string at the current iteration, returning true if the strings are equal (if the string is in the lexicon set,
// it is a word by definition; isWord returns true)
bool WordLadder::isWord(string str)
{
	for (set<string>::iterator it = lexicon.begin(); it != lexicon.end(); ++it) // iterate over all the strings in the set
	{
		if (*it == str) // If the string at the current iteration equals the string we're looking for...
			return true; // ...then we've found the string in the set, thus str is a word- return true.
	}
	return false; // if we get here, we never took the return, thus str is not in the set, and it is not a word
}

// Checks to see if the given sequence of strings is a valid word ladder.  If the starting and ending strings of the sequence are
// valid words, and the sequence contains more than 1 string, then the word ladder represented by sequence is valid.
bool WordLadder::isWordLadder(vector<string> sequence)
{
	if (sequence.size() < 2)
		return false; // sequence is NOT a valid word ladder if there are fewer words than the minimum of 2 (consisting of at least the START and END word)
	if (!isWord(*sequence.begin()) || !isWord(*sequence.end()))
		return false; // sequence is NOT a valid word ladder if either START word or end word is not a word according to the dictionary.
	return true; // if we got here, we took neither of the returns above, thus sequence IS a valid word ladder by default.
}

// Returns the total number of words in the current lexicon.
int WordLadder::getWordCount()
{
	return lexicon.size();
}

// Used to display the result, whether empty, or a valid WordLadder.  Outputs either "Word Ladder is empty - No Solution" or 
// "A Shortest Word Ladder ([steps] steps) is:" where steps is one fewer than the size of the sequence of words from getMinLadder.
// If steps is -1, the sequence must have had 0 word strings, meaning getMinLadder could not find a valid word ladder.
void WordLadder::displayResult(vector<string> sequence)
{
	int steps = sequence.size() - 1;
	if (steps == -1) // If word ladder is empty 
	{
		// sequence from getMinLadder is empty; could not find a valid word ladder
		cout << "Word Ladder is empty - No Solution"; 
		exit(0); // nothing else to do in the program, so exit with no errors.
	}
	cout << "A Shortest Word Ladder (" << steps << " steps) is:";
	for (vector<string>::reverse_iterator it = sequence.rbegin(); it != sequence.rend(); ++it) // iterate through the sequence of word strings in REVERSE
		cout << ' ' << *it; // get the word string at the current iteration and output. The result is a properly ordered sequence of words with
							// on character of whitespace between each word.
	cout << endl;
}

// Returns all the words that have a Hamming distance of one relative to the given word by means of
// iterating over all the words in the dictionary, comparing every word to the given word's hamming distance,
// keeping a set of word strings to save every word that has a hamming distance of 1 (a neighbor to the given word by
// definition).  Lastly, after collecting all the neighbors into the set, return the resulting set.
set<string> WordLadder::getNeighbors(string word)
{
	set<string> neighbors; // Create an empty list of neighbors to [word]
	for (std::set<string>::iterator it = lexicon.begin(); it != lexicon.end(); ++it) 
		// Iterate over all the words in the dictionary
	{
		string currentWord = *it;
		int hammDist = getHammingDistance(word, currentWord); // Get the hamming distance between word and the current..
													  // ...word found in the dictionary
		if (hammDist == 1) // If the distance is 1, the words are adjacent (neighbors) by definition.
			neighbors.insert(currentWord); // Add the adjacent word to the list of neighbors
	}
	return neighbors;
}

// Returns the Hamming distance between two strings, str1 and str2. The Hamming distance between two
// strings of equal length is defined as the number of positions at which the corresponding symbols
// are different. Returns -1 if the strings have different lengths (the Hamming distance is undefined)
int WordLadder::getHammingDistance(string str1, string str2)
{
	int len = str1.length();
	if (len != str2.length()) // Make sure the words have equal lengths
		return -1; // The hamming distance is -1 if the words have different lengths. Stop here.
	int dist = len; // At first, the distance will be at most the length of the strings
	for (int i = 0; i < len; i++) // iterate through the strings, comparing every character from both words to each other
	{
		if (str1[i] == str2[i]) // If their respective characters sampled from the same position are the same...
			dist--; // ...the distance must be at least 1 closer, decrement dist
	}
	return dist; // the for loop has compared all characters and found the distance, so return it.
}

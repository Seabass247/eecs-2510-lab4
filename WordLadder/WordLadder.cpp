#include "WordLadder.h"
#include <iostream>
#include <fstream>
#include <list>

// The constructor. Creates the word ladder with a lexicon set containing the words read in 
// from a specified file, only keeping the words that have length [len].
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
	// the specified length [len]
	std::string word;
	while (file >> word) // Insert all the appropriate-length words into the lexicon set
	{
		if (word.length() != len) // Skip over words with the incorrect length
			continue;
		lexicon.insert(word); // Insert the word
		//cout << "Insert: " << word << endl; // Debug print
	}
}

// Returns a minimum-length word ladder from start to end. If multiple minimum-length
// word ladders exist, no guarantee is made regarding which one is returned. If no word
// ladder exists, this method returns an empty list. Uses a breadth-first search.
//
// start    the starting word
// end      the ending word
// returns  a minimum length word ladder from start to end
//
vector<string> WordLadder::getMinLadder(string start, string end)
{
	vector<string> ladder; // start with an empty ladder,
	vector<string> wordsSeen; // list of words seen,
	vector<string> wordPredecessors; // and list of every word's predecessor

	list<string> queue;
	queue.push_back(start); // Start with the queue containing the first word in the ladder
	// TODO Mark the first word as seen?
	wordsSeen.push_back(start);
	// TODO Set the first word's predecessor to ""?
	wordPredecessors.push_back("");

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
					
					return ladder;
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
	return vector<string>();
}

// Returns the location within the vector of the given string; returns -1 if not found
int WordLadder::findInVector(vector<string> vec, string str)
{
	int location = -1;
	for (std::vector<string>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		location++; // Move the location of the given string down 1
		if (*it == str) // If the value at the current iteration equals the string we're looking for
			return location; // return the location of said string in the vector
	}
	// If we got here, we never took the return, thus the string was not found in the vector
	return -1;
}

void WordLadder::displayResult(vector<string> sequence)
{
	int steps = sequence.size() - 1;
	if (steps == -1) // If word ladder is empty 
	{
		cout << "Word Ladder is empty - No Solution";
		exit(0);
	}
	cout << "A Shortest Word Ladder (" << steps << " steps) is:";
	for (vector<string>::reverse_iterator it = sequence.rbegin(); it != sequence.rend(); ++it)
		cout << ' ' << *it;
	cout << endl;
}

// Returns all the words that have a Hamming distance of one relative to the given word.
//
// word:     the given word
// returns:  the neighbors of the given word
//
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
// str1    the first string
// str2    the second string
// returns the Hamming distance between str1 and str2 if they are the same length, -1 otherwise
int WordLadder::getHammingDistance(string str1, string str2)
{
	int len = str1.length();
	if (len != str2.length()) // Make sure the words have equal lengths
		return -1; // The hamming distance is -1 if the words have different lengths. Stop here.
	int dist = len; // First, the distance will be at most the length of the strings
	for (int i = 0; i < len; i++) // iterate through the strings, comparing every character from both words to eachother
	{
		if (str1[i] == str2[i]) // If the character at their respective position are the same...
			dist--; // the distance must be at least 1 less
	}
	return dist;
}

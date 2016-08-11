
#include "Hashtable.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  HashTable ht;
  ifstream input("dict.txt");
  if (!input) {
    cerr << "Error in reading the file dict.txt." << endl;
    return -1;
  } else {
    string s;
    while (true) {
      getline(input, s);
      if (input.eof()) {
	break;
      } else {
	// Insert the key (word) into the hashtable
	ht.insert(s);
      }
    }
  }

  while(true) {
    cout << "Lookup: " << endl;
    string word;
    cin >> word;
    if (word == ".") break;
    // Look up a word
    if (ht.lookup(word)) {
      cout << "Found the word in the dictionary" << endl;
    } else {
      cout << "Cannot find the word in the dictionary" << endl;
    }
  }
  
  return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Array.h"
#include "bst.h"
#include "SplayTree.h"

using namespace std;


void dumpSplayTree(SplayTree<string, Array<string> >& spt,
                   string aFilename)
{
    ofstream ofs(aFilename);
    ofs << spt;    
}

void insertWithGrouping(SplayTree<string, Array<string> >& aSplayTree,
			string aArtist,
			string aMusicEntry)
{
    static int debug_count = 0;
    ostringstream os;
    os << "debug" << debug_count++ << ".dot";
    string filename = os.str();
 
    // Here aArtist is the key and aMusicEntry contributes toward the value
    BSTNode<string, Array<string> >* place = aSplayTree.findInsertionPoint(aArtist);
    if (place == nullptr) {
        // First node to be inserted
        Array<string> musicList;
        musicList.add(aMusicEntry);
        aSplayTree.setRoot(new BSTNode<string, Array<string> >(aArtist, musicList));
    } else if (aArtist == place->key()) {
        // Key matched
        // aArtist exists -- just group the current aMusicEntry with the existing
        // associated musicList
        Array<string> musicList = place->value();
        // Aggregation
        musicList.add(aMusicEntry);
        // Replace the value with the updated musicList
        place->setValue(musicList);
	// Splay this node as it is just augmented
	aSplayTree.splay(place);
    } else {
        // Key not matched
        // So, this is going to be the first music entry for aArtist
        Array<string> musicList;
        musicList.add(aMusicEntry);
        BSTNode<string, Array<string> >* newNode =
            new BSTNode<string, Array<string> >(aArtist, musicList,
                                                nullptr, nullptr, place);

        if (aArtist < place->key()) {
            // Node on the left of place
            place->setLeft(newNode);
        } else {
            // Node on the right of place
            place->setRight(newNode);
        }
	// dumpSplayTree(aSplayTree, filename);
        aSplayTree.splay(newNode);
    }
}

void processInput(string& aInput, string& aArtist, string& aMusicEntry)
{
    size_t dashPos = aInput.find("-");
    if (dashPos == string::npos) {
        cerr << "Invalid Entry: No dash in: " << aInput << endl;
        return;
    }
    aArtist = aInput.substr(0, dashPos-1);
    aMusicEntry = aInput.substr(dashPos+1);
}

int main(int argc, char** argv)
{

    if (argc != 2) {
        cerr << "Provide the music file to process as an argument to the program." << endl;
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        exit(1);
    }
    
    // key --> artist name (string)
    // value --> Array of songs (array of strings)
    SplayTree<string, Array<string> > splayTree;
  
    ifstream ifs(argv[1]);
    string line;
    while(getline(ifs, line)) {
        string artist, musicEntry;
        processInput(line, artist, musicEntry);
        insertWithGrouping(splayTree, artist, musicEntry);
    }

    // Dump the initial splay tree
    dumpSplayTree(splayTree, "splay_tree0.dot");

    int count = 0;
    // Insertion into the splay tree is done
    // Now, let's go through the motions of inserting, deleting or finding
    while (true) {
        int input;
        ostringstream os;
        os << "splay_tree" << ++count << ".dot";
        string filename = os.str();
        cout << "Input choices:" << endl;
        cout << "* Insert (1)" << endl;
        cout << "* Find (2)" << endl;
        cout << "* Remove (3)" << endl;
        cout << "* Print sorted (4)" << endl;
        cout << "* Exit(0)" << endl;
        cin >> input;
        cin.ignore(256, '\n');
        switch(input) {
          case 1: {
              string artist, musicEntry;
              cout << "Artist: ";
              getline(cin, artist);
              cout << "Music: ";
              getline(cin, musicEntry);
              insertWithGrouping(splayTree, artist, musicEntry);
              dumpSplayTree(splayTree, filename);
              cout << "Done." << endl;
              break; 
          }
          case 2: {
              cout << "Find what (Enter artist name): ";
              string artist;
              getline(cin, artist);
              BSTNode<string, Array<string> >* approxMatchNode_lb = nullptr;
              BSTNode<string, Array<string> >* approxMatchNode_ub = nullptr;
              BSTNode<string, Array<string> >* node = 
                  splayTree.findApprox(artist, approxMatchNode_lb, approxMatchNode_ub);
              dumpSplayTree(splayTree, filename);
              if (node != nullptr) {
                  cout << "Accurately matched!" << endl;
              } else {
                  cout << "Approximate matches: " << endl;
                  if (approxMatchNode_lb) {
                      cout << "Artist: " << approxMatchNode_lb->key() << endl;
                      cout << "Songs: " << approxMatchNode_lb->value() << endl;
                  }
                  if (approxMatchNode_ub) {
                      cout << "Artist: " << approxMatchNode_ub->key() << endl;
                      cout << "Songs: " << approxMatchNode_ub->value() << endl;
                  }
              }
              break;
          }
          case 3: {
              cout << "Remove what (Enter artist name): ";
              string artist;
              getline(cin, artist);
              splayTree.remove(artist);
              dumpSplayTree(splayTree, filename);
              cout << "Done." << endl;
              break; 
          }
          case 4: {
              cout << "Sorted List: " << endl;
              splayTree.inorder();
              cout << "Done." << endl;
              break; 
          }
          case 0: {
              cout << "Exiting..." << endl;
              return 0;
          }
          default: {
              cout << "Invalid entry: Try again." << endl;
              break;
          }
        }
    }

    return 0;
}
 

// Hashtable.h
// defines the hastable class
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include "Array.h"
#include "sll.h"
using namespace std;

class HashTable{
public:
	//Default constructor
	HashTable(){
		buckets = Array<SLinkedList<string>*>(500009);
		size = 500009;
		for(int i = 0; i < size; i++){
			buckets[i] = new SLinkedList<string>();
		}
	}
	//Destructor
	~HashTable(){
		for(int i = 0; i < size; i++){
			buckets[i]->removeAll();
		}
	}
	//insertion function
	void insert(string s){
		int hashval = hashcode(s);
		int bucket_index = h(hashval);
		buckets[bucket_index]->addBack(s);
	}
	//lookup function
	bool lookup(string word){
		int hashval = hashcode(word);
		int bucket_index = h(hashval);
		SLLNode<string>* curr = buckets[bucket_index]->head();
		while(curr != NULL){
			if (curr->value() == word){
				return true;
			}
			curr = curr->next();
		}
		return false;
	}
private:
	//converting the string to an integer value
	int hashcode(string s){
		int hashval = 0;
		for(int i =0; i < s.length(); i++){
			hashval = (127*hashval+s[i])%16908799;
		}
		return hashval;
	}
	//determines the bucket in which it shall sit
	int h(int hashcode){
		//asigning primes-- can not do random since there is a need for consistancy
		int p = 16908799;
		int b = 2500071; 
		int a = 29;
		int h = ((a*hashcode+b)%p)%size;
        return h;
	}

    Array<SLinkedList<string>*> buckets;
    int size;
};


#endif

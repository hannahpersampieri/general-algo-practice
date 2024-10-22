
#include "sll.h"

using namespace std;

SLinkedList::SLLNode* SLinkedList::mergesort(SLinkedList::SLLNode* aHead)
{
	//termination condition
	if(aHead == NULL or aHead->next() == NULL){
		return aHead;
	}
	//find "midpoint"
	SLinkedList::SLLNode* mid = goToMid(aHead);
	SLinkedList::SLLNode* secondHead = mid->next();
	mid->setNext(NULL);
	return merge(mergesort(aHead),mergesort(secondHead));
}
SLinkedList::SLLNode* SLinkedList::goToMid(SLinkedList::SLLNode* aHead){
	SLinkedList::SLLNode* p1 = aHead;
	SLinkedList::SLLNode* p2 = aHead;
	while(p2->next() != NULL &&  p2 ->next()->next() != NULL && p1->next() != NULL){
		p2 = p2->next()->next();
		p1 = p1->next();
	}
	return p1;
}
SLinkedList::SLLNode* SLinkedList::merge(SLinkedList::SLLNode* h1, SLinkedList::SLLNode* h2){
	//make a dummy node, and copy it
	SLinkedList::SLLNode* dummy = new SLinkedList::SLLNode(0);
	SLinkedList::SLLNode* result = dummy;
	//traverse the two lists
	for(; h1 != NULL && h2 != NULL; result = result->next()){
		if(h1->value() <= h2->value()){
			result->setNext(h1);
			h1 = h1->next();
		}
		else{
			result->setNext(h2);
			h2 = h2->next();
		}
	}
	//check conditions for terminating the loop
	if(h1 == NULL){
		result->setNext(h2);
	}
	else{
		result->setNext(h1);
	}
	//make a temporary node to store the dummy 
	SLinkedList::SLLNode* temp = dummy->next();
	delete dummy;
	return temp;
}
void SLinkedList::sort(){
	mergesort(head());
}

/// Overloaded operator<< for outputing a list
ostream& operator<<(ostream& s, const SLinkedList& aList)
{
  aList.output(s);
  return s;
}

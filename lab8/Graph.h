
#ifndef GRAPH_H
#define GRAPH_H

#include "sll.h"

#define INFINITY 100000

class Edge;

class Node {
 public:

  Node(int aId) 
    : mId(aId), 
    mEdges(), 
    mShortestDistance(INFINITY), 
    mShortestParent(NULL)
  {}

  int id() const { return mId; }
  void addEdgeTo(Edge* e) { mEdges.add(e); }
  int numEdges() const { return mEdges.size(); }
  SLinkedList<Edge*>& getEdges() { return mEdges; }
  
  void setShortestDistance(int aDist) { mShortestDistance = aDist; }
  int shortestDistance() const { return mShortestDistance; }
  void setShortestParent(Edge* p) { mShortestParent = p; }
  Edge* shortestParent() { return mShortestParent; }
  const Edge* shortestParent() const { return mShortestParent; }

  // Key to be used in the heap
  int key() const { return shortestDistance(); }

 private:
  int mId;
  SLinkedList<Edge*> mEdges;
  // shortest distance from the start node
  int mShortestDistance;
  // Parent pointer on the shortest path
  Edge* mShortestParent;
};

class Edge {
 public:
  Edge(Node* n1, 
       Node* n2, 
       int w = 0, 
       std::string aName = "") 
    : mFrom(n1), mTo(n2), mWeight(w), mName(aName)
  {}

  Node* source() { return mFrom; }
  Node* sink() { return mTo; }
  const Node* source() const { return mFrom; }
  const Node* sink() const { return mTo; }

  int weight() const { return mWeight; }
  void setWeight(int aWeight) { mWeight = aWeight; }

  std::string& name() { return mName; }

 private:
  Node* mFrom;
  Node* mTo;
  int mWeight;
  std::string mName;
};

class Graph {
 public:
  int numNodes() const { return mNodes.size(); }
  void addNode(int aId)
  {
    Node* aNode = new Node(aId);
    mNodes.add(aNode);
  }
  
  Node* find(int aId) const
  {
    for (const SLLNode<Node*>* curr = mNodes.head();
	 curr != NULL; curr = curr->next()) {
      if (curr->value()->id() == aId) {
	return curr->value();
      }
    }
    return NULL;
  }

  void addEdge(int aNodeId1, 
	       int aNodeId2, 
	       int aWeight = 0,
	       std::string aName = "")
  {
    Node* n1 = find(aNodeId1);
    Node* n2 = find(aNodeId2);
    if (n1 != NULL && n2 != NULL) {
      Edge *e = new Edge(n1, n2, aWeight, aName);
      mEdges.add(e);
      n1->addEdgeTo(e);
    }
  }

  // Output the graph in dotty format
  void output(std::ostream& s) const;

  // Compute shortest paths from aNodeId
  void computeShortestPaths(int aNodeId);

  // Print directions
  void printDirectionsTo(Node* aNode) const;

  ~Graph(){
    mEdges.removeAll();
    delete mEdges.head();
    mNodes.removeAll();
    delete mNodes.head();
  }
  
 private:

  void initializeShortestPath(int aStartNodeId);
  void relax(Edge* e);

  void outputNodes(std::ostream& s) const;
  void outputEdges(std::ostream& s) const;
 private:
  SLinkedList<Node*> mNodes;
  SLinkedList<Edge*> mEdges;
};

std::ostream& operator<<(std::ostream& s, const Graph& g);

#endif

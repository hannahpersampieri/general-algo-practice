
#include "Graph.h"
#include "Heap.h"

void Graph::outputNodes(std::ostream& s) const
{
  if (mNodes.size() == 0) {
    return;
  }
  for (const SLLNode<Node*>* curr = mNodes.head();
       curr != NULL; curr = curr->next()) {
    Node* n = curr->value();
    s << n->id() 
      << " [label="
      << "\""
      << n->id()
      << " (" << n->shortestDistance() << ")"
      << "\"" 
      << "]"
      << " [shape=box];"
      << std::endl;
  }
}

void Graph::outputEdges(std::ostream& s) const
{
  if (mEdges.size() == 0) {
    return;
  }
  for (const SLLNode<Edge*>* curr = mEdges.head();
       curr != NULL; curr = curr->next()) {
    Edge* e = curr->value();
    s << e->source()->id() << " -> " << e->sink()->id() 
      << " [label="
      << "\""
      << e->name()
      << " (" << e->weight() << ")"
      << "\"" 
      << "];"
      << std::endl;
  }
}

void Graph::output(std::ostream& s) const
{
  s << "digraph{" << std::endl;
  outputNodes(s);
  outputEdges(s);
  s << "}" << std::endl;
}

void Graph::initializeShortestPath(int aStartNodeId)
{
  for (const SLLNode<Node*>* curr = mNodes.head();
       curr != NULL; curr = curr->next()) {
    Node* currNode = curr->value();
    currNode->setShortestDistance(INFINITY);
    currNode->setShortestParent(NULL);
  }
  Node* startNode = find(aStartNodeId);
  startNode->setShortestDistance(0);
}

// Dijkstra's algorithim for computing shortest path
void Graph::computeShortestPaths(int aNodeId)
{
  initializeShortestPath(aNodeId);

  Heap<Node*> heap(numNodes());

  // Insert all the nodes into the heap
  for (const SLLNode<Node*>* curr = mNodes.head();
       curr != NULL; curr = curr->next()) {
    Node* currNode = curr->value();
    heap.insertIgnoringHeapOrder(currNode);
  }

  // Heapify into a min heap
  heap.bottomUpMinHeap();

  // You can call heap.removeMin() to extract the min
  while(!heap.isEmpty()){
    Node* u = heap.removeMin();
    SLinkedList<Edge*> edges = u->getEdges();
    for (SLLNode<Edge*>* curr = edges.head();
       curr != NULL; curr = curr->next()){
        Edge* e = curr->value();
        relax(e);
    }
    heap.bottomUpMinHeap();
  }

}
void Graph::relax(Edge* e){
          Node* u = e->source();
          Node* v = e->sink();
          int w = e->weight();
          if (v->shortestDistance() > u->shortestDistance() + w){
            v->setShortestDistance(u->shortestDistance() + w);
            v->setShortestParent(e);
     }
}
void Graph::printDirectionsTo(Node* aNode) const
{
  Edge* parentEdge = aNode->shortestParent();
  if (parentEdge == NULL) {
    return;
  }
  Node* source = parentEdge->source();
  printDirectionsTo(source);
  
  cout << "Drive for " << parentEdge->weight() << " meters";
  cout << " on " << parentEdge->name() << endl;
}

std::ostream& operator<<(std::ostream& s, const Graph& g)
{
  g.output(s);
}


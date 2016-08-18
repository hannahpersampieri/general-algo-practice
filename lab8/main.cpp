
#include "Graph.h"

using namespace std;

int main()
{
  Graph g;
  int numNodes = 26;
 
  for (int i = 0; i < numNodes; ++i) {
    g.addNode(i);
  }
  
  /*g.addEdge(0, 1, 50, "Joy St");
  g.addEdge(1, 9, 200, "Pinckney St");
  g.addEdge(1, 5, 55, "Joy St");
  g.addEdge(5, 22, 80, "Joy St");
  g.addEdge(22, 21, 120, "Joy St");
  g.addEdge(2, 3, 35, "Derne St");
  g.addEdge(3, 4, 35, "Derne St");
  g.addEdge(4, 5, 55, "Derne St");
  g.addEdge(5, 6, 80, "Derne St");
  g.addEdge(6, 7, 30, "Derne St");
  g.addEdge(7, 8, 40, "Derne St");
  g.addEdge(8, 10, 70, "Derne St");
  g.addEdge(23, 4, 200, "Hancock St");
  g.addEdge(4, 0, 160, "Hancock St");
  g.addEdge(3, 24, 200, "Ridgeway Ln");
  g.addEdge(2, 25, 200, "Staniford St");
  g.addEdge(9, 10, 50, "Anderson St");
  g.addEdge(10, 11, 30, "Anderson St");
  g.addEdge(11, 14, 80, "Anderson St");
  g.addEdge(14, 17, 90, "Anderson St");
  g.addEdge(11, 12, 70, "Revere St");
  g.addEdge(12, 13, 40, "Revere St");
  g.addEdge(16, 15, 45, "Phillips St");
  g.addEdge(15, 14, 70, "Phillips St");
  g.addEdge(8, 12, 30, "Garden St");
  g.addEdge(12, 15, 80, "Garden St");
  g.addEdge(15, 18, 90, "Garden St");
  g.addEdge(13, 7, 30, "Irving St");
  g.addEdge(16, 13, 80, "Irving St");
  g.addEdge(19, 16, 90, "Irving St");
  g.addEdge(20, 6, 200, "S Russell St");
  g.addEdge(17, 18, 75, "Cambridge St");
  g.addEdge(18, 19, 50, "Cambridge St");
  g.addEdge(19, 20, 30, "Cambridge St");
  g.addEdge(20, 21, 70, "Cambridge St");
  g.addEdge(21, 23, 50, "Cambridge St");
  g.addEdge(23, 24, 35, "Cambridge St");
  g.addEdge(24, 25, 35, "Cambridge St"); */
  g.addEdge(0, 1, 50, "Joy St");
  g.addEdge(1, 9, 200, "Pinckney St");
  g.addEdge(1, 5, 55, "Joy St");
  g.addEdge(5, 22, 80, "Joy St");
  g.addEdge(22, 21, 120, "Joy St");
  g.addEdge(2, 3, 35, "Derne St");
  g.addEdge(3, 4, 35, "Derne St");
  g.addEdge(4, 5, 55, "Derne St");
  g.addEdge(6, 5, 80, "Myrtle St");
  g.addEdge(7, 6, 30, "Myrtle St");
  g.addEdge(8, 7, 40, "Myrtle St");
  g.addEdge(10, 8, 70, "Myrtle St");
  g.addEdge(23, 4, 200, "Hancock St");
  g.addEdge(4, 0, 160, "Hancock St");
  g.addEdge(3, 24, 200, "Ridgeway Ln");
  g.addEdge(2, 25, 200, "Staniford St");
  g.addEdge(9, 10, 50, "Anderson St");
  g.addEdge(10, 11, 30, "Anderson St");
  g.addEdge(11, 14, 80, "Anderson St");
  g.addEdge(14, 17, 90, "Anderson St");
  g.addEdge(11, 12, 70, "Revere St");
  g.addEdge(12, 13, 40, "Revere St");
  g.addEdge(16, 15, 45, "Phillips St");
  g.addEdge(15, 14, 70, "Phillips St");
  g.addEdge(8, 12, 30, "Garden St");
  g.addEdge(12, 15, 80, "Garden St");
  g.addEdge(15, 18, 90, "Garden St");
  g.addEdge(13, 7, 30, "Irving St");
  g.addEdge(16, 13, 80, "Irving St");
  g.addEdge(19, 16, 90, "Irving St");
  g.addEdge(20, 6, 200, "S Russell St");
  g.addEdge(17, 18, 75, "Cambridge St");
  g.addEdge(18, 19, 50, "Cambridge St");
  g.addEdge(19, 20, 30, "Cambridge St");
  g.addEdge(20, 21, 70, "Cambridge St");
  g.addEdge(21, 23, 50, "Cambridge St");
  g.addEdge(23, 24, 35, "Cambridge St");
  g.addEdge(24, 25, 35, "Cambridge St");

  cout << g;

  g.computeShortestPaths(0);

  cout << "After shortest paths have been annotated:" << endl;
  cout << g;

  cout << "Driving directions from node 0 (Hancock and Joy) to node 20 (Cambridge and S Russell):" << endl;
  Node* target = g.find(20);
  g.printDirectionsTo(target);
  cout << "Total distance = " << target->shortestDistance() << " meters." << endl;

  return 0;
}

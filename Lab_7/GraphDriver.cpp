// CSCI 311 - Spring 2021
// Lab 7 Driver
// Author: Carter Tillquist

#include <iostream>
#include <vector>
#include <string>
#include "Node.h"
#include "Graph.h"
#include <limits.h>
using namespace std;

Graph makeGraph();
int main(){
  cout << "MAKE GRAPH" << endl;
  Graph G = makeGraph();

  cout << "ADJACENCY LIST" << endl;
  G.printAdjList();

  cout << "CHECK NEIGHBORS" << endl;
  int num = -1;
  cin >> num;
  for (int i = 0; i < num; i++){
    int u = -1, v = -1;
    cin >> u >> v;
    cout << u << " " << v << " " << (G.isNeighbor(u, v) ? "True": "False") << endl;
  }

  cout << "DFS" << endl;
  G.DFS();
  for (int i = 0; i < G.nodes.size(); i++){
    cout << G.nodes[i].id << ": " 
         << (G.nodes[i].visited ? "True" : "False") << ", "
         << G.nodes[i].discovered << ", "
         << G.nodes[i].finished << ", "
         << ((G.nodes[i].predecessor != nullptr) ? G.nodes[i].predecessor->id : -1) << endl;
  }

  cout << "BFS / DISTANCES FROM" << endl;
  cin >> num;
  for (int i = 0; i < num; i++){
    int s = -1;
    cin >> s;
    vector<int> dists = G.distancesFrom(s);
    cout << "source " << s << ": ";
    for (int j = 0; j < G.nodes.size(); j++){
      cout << "(to " << G.nodes[j].id << ": " 
           << ((G.nodes[j].dist == INT_MAX) ? -1 : G.nodes[j].dist) << ", "
           << ((dists[j] == INT_MAX) ? -1 : dists[j]) << ") ";
    }
    cout << endl;
  }
  
  cout << "DONE" << endl;
  
  return 0;
}

/*******************************************************************************************************************
 * A function to collect input from the user for making a simple graph. The first line of input should include two *
 * integers, n and m, representing the number of nodes and the number of edges in the graph. The following m lines *
 * each contain a pair of space separated integers representing edges in the graph.                                *
 * return - Graph - a graph constructed based on the user input                                                    *
 * *****************************************************************************************************************/
Graph makeGraph(){
  int n = 0, m = 0;
  cin >> n >> m;
  Graph G;
  for (int i = 0; i < n; i++){
    Node v(i);
    G.nodes.push_back(v);
  }
  for (int i = 0; i < m; i++){
    int u = -1, v = -1;
    cin >> u >> v;
    G.nodes[u].neighbors.push_back(&G.nodes[v]);
    G.nodes[v].neighbors.push_back(&G.nodes[u]);
  }
  return G;
}

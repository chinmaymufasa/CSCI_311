// CSCI 311 - Spring 2021
// Lab 8 Driver
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

  cout << "IS TWO COLORABLE" << endl;
  cout << (G.isTwoColorable() ? "true" : "false") << endl;

  cout << "IS CONNECTED" << endl;
  cout << (G.isConnected() ? "true" : "false") << endl;

  cout << "HAS CYCLE" << endl;
  cout << (G.hasCycle() ? "true" : "false") << endl;

  cout << "IS REACHABLE" << endl;
  int num = -1;
  cin >> num;
  for (int i = 0; i < num; i++){
    int u = -1, v = -1;
    cin >> u >> v;
    cout << u << " " << v << " " << (G.isReachable(u, v) ? "True": "False") << endl;
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

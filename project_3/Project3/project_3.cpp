// CSCI 311 - Spring 2021
// project_3 cpp
// Author: Chinmay Satpanthi

#include <iostream>
#include <vector>
#include <string>
#include <limits.h>

#include "Graph.h"

using namespace std;

int main() {
   Graph *G = new Graph();    //creats new graph
   G->setMap();               //runs the mapping in Dijkstra's algorithm
   G->printRoute();           //prints the route
   
   return 0;
}


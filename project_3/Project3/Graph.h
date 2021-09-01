// CSCI 311 - Spring 2021
// Graph class header
// Author: Chinmay Satpanthi

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Node.h"

class Graph {
public:
   vector<Node> nodes;  //holds all the nodes
   
   Graph();             //constructor
   
   void setMap();       //sets the values of graph
   void Dijkstra(int);  //runs the Dijkstra's algorithm
   void printRoute();   //prints the route

   private:
      //graph and map variables
      int source ;   
      int destination ;
      int max_charge;
      vector<vector<int>> edge;
};

#endif
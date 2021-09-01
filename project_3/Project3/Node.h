// CSCI 311 - Spring 2021
// Node Class
// Author: Chinmay Satpanthi

#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
using namespace std;

class Node {
public:
   
   //Node variables
   
   int id;
   int dist;
   int destination_dist;
   bool charge_station;
   int current_charge;
   int nodes_visit;

   Node* predecessor;
   vector<Node*> neighbors;
   vector< pair<int, int>> weights;   
   
   //constructor
   Node();
   Node(int);
};

#endif

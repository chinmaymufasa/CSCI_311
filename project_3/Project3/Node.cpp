// CSCI 311 - Spring 2021
// Node cpp
// Author: Chinmay Satpanthi


#include <string>
#include <vector>
#include <limits.h>
#include "Node.h"


Node::Node() {
   id = 0;
   dist = INT_MAX;                  //distanct from node
   destination_dist = INT_MAX;      //destination locals
   charge_station = false;          //charge station bool
   current_charge = -1;             //current range on car
   nodes_visit = -1;                //number of stops
   predecessor = nullptr;           //parents
   neighbors = {};                  //neighbors
   weights = {};                    //graph edges
}

Node::Node(int i) {
   id = i;
   dist = INT_MAX;
   destination_dist = INT_MAX;
   charge_station = false;
   current_charge = -1;
   nodes_visit = -1;
   predecessor = nullptr;
   neighbors = {};
   weights = {};
}
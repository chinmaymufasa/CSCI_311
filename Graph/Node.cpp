// CSCI 311 - Spring 2021
// Node cpp
// Author: Carter Tillquist


#include <string>
#include <vector>
#include <limits.h>
#include "Node.h"


Node::Node() {
   id = 0;
   dist = INT_MAX;
   discovered = -1;
   finished = -1;
   visited = false;
   color = "";
   predecessor = nullptr;
   neighbors = {};
}

Node::Node(int i) {
   id = i;
   dist = INT_MAX;
   discovered = -1;
   finished = -1;
   visited = false;
   color = "";
   predecessor = nullptr;
   neighbors = {};
}
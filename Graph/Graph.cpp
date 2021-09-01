// CSCI 311 - Spring 2021
// Graph class cpp
// Author: Carter Tillquist, Chinmay Satpanthi

#include <iostream>
#include "Graph.h"
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

Graph::Graph() {
}

/*
print adjacent nodes from the current node
*/
void Graph::printAdjList() {
   for (int i = 0; i < nodes.size(); i++) {
      printf("%i: ", nodes[i].id);
      for (int j = 0; j < nodes[i].neighbors.size(); j++) {    //finds all the neighbors from the current node
         printf("%i ", nodes[i].neighbors[j]->id);
      }
      printf("\n");
   }
}

/*
* checks whether two elements are neghbors of each other
*/
bool Graph::isNeighbor(int u, int v) {
   for (int i = 0; i < nodes[u].neighbors.size(); i++) {
      if (nodes[u].neighbors[i]->id == v) {                 //compares value at u and value at v
         return true;
      }
   }
   return false;
}

/*
Depth First Search Algorithm
*/
void Graph::DFS() {

   for (int i = 0; i < nodes.size(); i++) {        //intializes all values in node to defualt
      nodes[i].visited = false;
      nodes[i].predecessor = NULL;
      nodes[i].discovered = -1;
      nodes[i].finished = -1;
   }

   int time = 0;                                    //timer count
   for (int i = 0; i < nodes.size(); i++) {         //loop checks u nodes for visit
      if (nodes[i].visited == false) {
         time = DFSVisit(i, time);                   //calls the helper function
      }
   }
}

/*
DFS visit function checks and updates all node visited during recursion
*/

int Graph::DFSVisit(int s, int time) {
   time = time + 1;
   nodes[s].discovered = time;                              //sets visit time
   nodes[s].visited = true;
   for (int i = 0; i < nodes[s].neighbors.size(); i++) {    //goes through all neighborhood nodes
      if (nodes[s].neighbors[i]->visited == false) {
         nodes[s].neighbors[i]->predecessor = &nodes[s];    //sets predecessor from priour node
         time = DFSVisit(nodes[s].neighbors[i]->id, time);  //new time
      }
      else if (nodes[s].predecessor != NULL &&
         nodes[s].predecessor->id != nodes[s].neighbors[i]->id){     //slightly modified DFS with an additional loop check
         nodes[i].color = "white";                          //sets color of node to white suggesting cycle
      }
   }
   time++;
   nodes[s].finished = time;                                //sets the finish time
   return time;
}

/*
Breath first search algorithm
*/
void Graph::BFS(int s) {
   for (int i = 0; i < nodes.size(); i++) {    //initializes all values
      nodes[i].dist = INT_MAX;
      nodes[i].visited = false;
      nodes[i].predecessor = NULL;
      nodes[i].color = "";
   }

   nodes[s].dist = 0;                          //sets default node to 0
   nodes[s].visited = true;
   nodes[s].color = "blue";                    //set initial color to blue

   queue<int> Q;                               //initial queue
   Q.push(s);

   while (!Q.empty()) {                        //checks all queue values

      int u = Q.front();                       //first element in q

      Q.pop();

      for (int i = 0; i < nodes[u].neighbors.size(); i++) {       //all the neighbors in the first element
         if (nodes[u].neighbors[i]->visited == false) {
            nodes[u].neighbors[i]->dist = nodes[u].dist + 1;      //adds distance + 1 to neighbors nodes
            nodes[u].neighbors[i]->visited = true;                //sets visit to true
            Q.push(nodes[u].neighbors[i]->id);                    //adds the next value to queue
            nodes[u].neighbors[i]->predecessor = &nodes[u];       //sets up the predecessor for prior node
            if (nodes[u].color == "blue") {                       //checks if prior node was blue and assigns red
               nodes[u].neighbors[i]->color = "red";
            }
            else if (nodes[u].color == "red") {                   //checks for red color and assigns blue
               nodes[u].neighbors[i]->color = "blue";
            }
         }
      }

   }

}

/*
finds the distance between a given source to all the nodes it can reach to using BFS
*/
vector<int> Graph::distancesFrom(int s)
{
   vector<int> distances;
   BFS(s);
   for (int i = 0; i < nodes.size(); i++) {     //pushes all distance value to vector
      int distance = nodes[i].dist;
      distances.push_back(distance);
   }
   return distances;
}


/*
This function checks if two adjacent edges has the same color or not
*/
bool Graph::isTwoColorable() {
   BFS(0);                                   //run thr BFS 
   if (nodes.size() == 1) {
      return true;
   }
   else if (nodes.size() > 1) {
      for (int i = 0; i < nodes.size(); i++) {
         for (int j = 0; j < nodes[i].neighbors.size(); j++) {          //skip out disconnected nodes
            if (nodes[i].color == "") {
               continue;
            }
            if (nodes[i].color == nodes[i].neighbors[j]->color) {       //if same color on adjacent return false
               return false;
            }
         }
      }
      return true;                           //if all check pass return true
   }
   else {
      return false;
   }
}


/*
This function checks if nodes are disconnected
*/
bool Graph::isConnected() {
   for (int i = 0; i < nodes.size(); i++) {
      if (nodes[i].color == "") {           //using the previous BFS is nodes dont have color
         return false;                      //it means BFS didnt get to them
      }
   }
   return true;
}


/*
Checks if graph has a cycle or a loop
*/
bool Graph::hasCycle() {   
   DFS();                                       //running the Depth First Search
   for (int i = 0; i < nodes.size(); i++) {     //There are some modifications in DFS
      if (nodes[i].color == "white") {          //using color white as cycle flag
         return true;
      }
   }
   return false;
}

/*
cycle recurring function
*/
bool Graph::hasCycleRecur(int s) {
   return false;
}

/*
checks if a nodes u v are connected
*/
bool Graph::isReachable(int u, int v) {
   BFS(u);                                     //BFS at index u
   if (nodes[v].color == "") {                 //if node v is blank then no path exists
      return false;
   }
   return true;
}
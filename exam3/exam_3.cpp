// CSCI 311 - Spring 2021
// Exam 3
// Author: Chinmay Satpanthi

#include <iostream>
#include <string>
#include <algorithm>
#include "Graph.h"
#include "Node.h"
using namespace std;

/************************************************************************************
 * A simple struct to represent directed edges                                      *
 * from - Node - the node at which the edge starts                                  *
 * to - Node - the node at which the edge ends                                      *
 * operator< - bool - defines an orderamong edges based on node ids of from then to *
 * **********************************************************************************/
struct Edge {
   Node from;
   Node to;
   bool operator<(const Edge& v) const {
      if (from.id < v.from.id) { return true; }
      if (from.id == v.from.id && to.id < v.to.id) { return true; }
      return false;
   }
};

/********************************************************************************************************
 * QUESTION 1                                                                                           *
 * Write a function that prints the expression associated with the given tree rooted at the given node. *
 * Note that the edges of T will be directed away from the root.                                        *
 * ******************************************************************************************************/
void printExpression(Graph T, int root) {

   if (!T.nodes.at(root).neighbors.empty()) {                        //checks if leaf node

      printExpression(T, T.nodes.at(root).neighbors.at(0)->id);      //recursively falls left side of tree
      if (!T.nodes.at(root).visited) {                               
         cout << T.nodes.at(root).data;                              //prints out the node if not yet visited
         T.nodes.at(root).visited = true;
      }
      if (T.nodes.at(root).neighbors.size() > 1) {                   //recursively checks the right side 
         printExpression(T, T.nodes.at(root).neighbors.at(1)->id);
      }
   }
   if (!T.nodes.at(root).visited) {
      cout << T.nodes.at(root).data;                                 //prints out the operator node
      T.nodes.at(root).visited = true;
   }
}

/****************************************************************************************************************************************************
 * QUESTION 2                                                                                                                                       *
 * Write a function that makes and returns an n by m grid graph. Vertices must be labeled in increasing order from left to right and top to bottom. *
 * **************************************************************************************************************************************************/
Graph makeGrid(int n, int m) {
   Graph G;
   int index = 0;                        //keep track of the number

   for (int i = 0; i < n*m; i++) {
      Node w(i);
      G.nodes.push_back(w);              //add the nodes to the graph
   }
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
         if (j < m - 1) {
            G.nodes[index].neighbors.push_back(&G.nodes[index + 1]);    //adds the horizontal edges to each others list
            G.nodes[index + 1].neighbors.push_back(&G.nodes[index]);
         }
         if (i < n - 1) {
            G.nodes[index].neighbors.push_back(&G.nodes[index + m]);    //adds the vertical edges to each others list
            G.nodes[index + m].neighbors.push_back(&G.nodes[index]);
         }
         index ++;                     //increments the index
      }
   }
   return G;
}

/***********************************************************************************************************
 * QUESTION 3                                                                                              *
 * Write a function that, given a directed graph, fills vectors with tree, forward, back, and cross edges. *
 * *********************************************************************************************************/

//This function checks if a node has a predecessor  
bool hasPredecessor(Graph& G, int s, int pred) {
   while (G.nodes[s].predecessor != NULL) {
      if (G.nodes[s].predecessor->id == pred) {
         return true;                           //has predecessor
      }
      s = G.nodes[s].predecessor->id;
   }
   return false;                                //does not have predecessor
}

//This function signature is provided if you would like to use it but you are not required to do so
int classifyEdgesRecur(int s, int time, Graph& G, vector<Edge>& tree, vector<Edge>& forward, vector<Edge>& back, vector<Edge>& cross) {
   Edge e;
   time = time + 1;
   G.nodes[s].discovered = time;                                                    //sets visit time
   G.nodes[s].visited = true;
   for (int i = 0; i < G.nodes[s].neighbors.size(); i++) {                          //goes through all neighborhood nodes
      e.from = G.nodes[s];
      e.to = *(G.nodes[s].neighbors[i]);
      if (G.nodes[s].neighbors[i]->visited == false) {
         tree.push_back(e);                                                         //if first time visit it is a tree edge
         G.nodes[s].neighbors[i]->predecessor = &G.nodes[s];                        //sets predecessor of prior node
         time = classifyEdgesRecur(G.nodes[s].neighbors[i]->id, time, G, tree, forward, back, cross);  //new time recursion
      }
      else if (hasPredecessor(G, G.nodes[s].id, G.nodes[s].neighbors[i]->id)) {     //checks if source node has neighbor as predecessor
         back.push_back(e);                                                         //back edge
      }
      else if (hasPredecessor(G, G.nodes[s].neighbors[i]->id, G.nodes[s].id)) {     //checks if neighbor node has source as predecessor
         forward.push_back(e);                                                      //front edge
      }
      else {
         cross.push_back(e);                                                        //all other are cross edges
      }
   }
   time++;
   G.nodes[s].finished = time;                                                      //sets the finish time
   return time;
}

//This function classifies the edges in graph as either tree, back, forward or cross
void classifyEdges(Graph& G, vector<Edge>& tree, vector<Edge>& forward, vector<Edge>& back, vector<Edge>& cross) {
   
   int time = 0;                                    
   for (int i = 0; i < G.nodes.size(); i++) {         
      if (G.nodes[i].visited == false) {
         time = classifyEdgesRecur(i, 0, G, tree, forward, back, cross);     //calls function on all unvisited nodes       
      }
   }
}

/********************************************************************************************************
 * TESTING                                                                                              *
 * When testing your functions, the main below expects input in a certain format for each question.     *
 * The first line of input should always the question number (1-3). More details are provided regarding *
 * the input for each question in the main itself.                                                      *
 * To test, you may run program and provide input by hand or you may provide a file as input directly   *
 * from the terminal For example, suppose you compile your program to a.out and that you have a file    *
 * named "test_1.in" containing input in the appropriate format for question 1. Then running            *
 * ./a.out < test_1.in                                                                                  *
 * will run your program using the lines of test_1.in as input. This can be a good way to save time and *
 * to save different test cases when testing your code.                                                 *
 * ******************************************************************************************************/
Graph makeAST();
Graph makeDirectedGraph();
int main() {
   int question = -1;
   cin >> question;

   //Declaring variables to use in the switch
   int n = -1, m = -1;
   vector<Edge> tree;
   vector<Edge> forward;
   vector<Edge> back;
   vector<Edge> cross;

   switch (question) {
   case 1: { // print expression
     /*************************************************************************************
      * Input format:                                                                     *
      * 1                                                                                 *
      * the number of nodes and edges in the tree separated by a space                    *
      * pairs of node ids and the string data to be held in the node separated by a space *
      * pairs of space separated integers representing tree edges                         *
      * ***********************************************************************************/
      cout << "PRINT EXPRESSION" << endl;
      Graph T = makeAST();
      printExpression(T, 0);
      break;
   }
   case 2: { // make grid
     /*******************************************************************
      * Input format:                                                   *
      * 2                                                               *
      * the number of rows and columns in the grid separated by a space *
      * *****************************************************************/
      cout << "MAKE GRID" << endl;
      cin >> n >> m;
      Graph G = makeGrid(n, m);
      G.printAdjList();
      break;
   }
   case 3: { // classify edges
     /*******************************************************************
      * Input format:                                                   *
      * 3                                                               *
      * the number of nodes and edges in the graph separated by a space *
      * pairs of space separated integers representing directed edges   *
      * *****************************************************************/
      cout << "CLASSIFY EDGES" << endl;
      Graph G = makeDirectedGraph();
      classifyEdges(G, tree, forward, back, cross);
      sort(tree.begin(), tree.end());
      sort(forward.begin(), forward.end());
      sort(back.begin(), back.end());
      sort(cross.begin(), cross.end());
      cout << "Tree edges: ";
      for (int i = 0; i < tree.size(); i++) { cout << "(" << tree[i].from.id << ", " << tree[i].to.id << ") "; }
      cout << endl;
      cout << "Forward edges: ";
      for (int i = 0; i < forward.size(); i++) { cout << "(" << forward[i].from.id << ", " << forward[i].to.id << ") "; }
      cout << endl;
      cout << "Back edges: ";
      for (int i = 0; i < back.size(); i++) { cout << "(" << back[i].from.id << ", " << back[i].to.id << ") "; }
      cout << endl;
      cout << "Cross edges: ";
      for (int i = 0; i < cross.size(); i++) { cout << "(" << cross[i].from.id << ", " << cross[i].to.id << ") "; }
      cout << endl;
      break;
   }
   default:
      break;
   }

   return 0;
}

/*****************************************************************************************************************************
 * A function to collect input from the user for making an abstract syntax tree. The first line of input should include two  *
 * integers, n and m, representing the number of nodes and the number of edges in the graph. The following n lines each      *
 * contain an integer representing a node and a string representing the data to be held in that node. The following m lines  *
 * each contain a pair of space separated integers representing directed edges in the graph.                                 *
 * return - Graph - an abstract syntax tree constructed based on the user input                                                              *
 * ***************************************************************************************************************************/
Graph makeAST() {
   int n = 0, m = 0;
   cin >> n >> m;
   int u = -1, v = -1;
   string data = "";
   Graph G;
   for (int i = 0; i < n; i++) {
      cin >> u >> data;
      Node w(u, data);
      G.nodes.push_back(w);
   }
   for (int i = 0; i < m; i++) {
      cin >> u >> v;
      G.nodes[u].neighbors.push_back(&G.nodes[v]);
   }
   return G;
}

/*********************************************************************************************************************
 * A function to collect input from the user for making a directed graph. The first line of input should include two *
 * integers, n and m, representing the number of nodes and the number of edges in the graph. The following m lines   *
 * each contain a pair of space separated integers representing directed edges in the graph.                         *
 * return - Graph - a graph constructed based on the user input                                                      *
 * *******************************************************************************************************************/
Graph makeDirectedGraph() {
   int n = 0, m = 0;
   cin >> n >> m;
   Graph G;
   for (int i = 0; i < n; i++) {
      Node v(i);
      G.nodes.push_back(v);
   }
   for (int i = 0; i < m; i++) {
      int u = -1, v = -1;
      cin >> u >> v;
      G.nodes[u].neighbors.push_back(&G.nodes[v]);
   }
   return G;
}
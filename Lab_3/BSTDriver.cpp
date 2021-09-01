// CSCI 311 - Spring 2021
// Lab 3 Solution - BST Driver
// Author: Carter Tillquist

#include <iostream>
#include <vector>
#include "BST.h"
using namespace std;

void printVector(const vector<Node*> &v);
void runSearch(BST* T);
void runInsert(BST* T);
void runDelete(BST* T);

/**************************************************
 * Simple main to test Binary Search Tree methods *
 * ************************************************/
int main(){
  BST* T = new BST();

  int operation;
  cin >> operation;

  while (operation > 0){
    vector<Node*> order;
    switch(operation){
      case 1: // search
        runSearch(T);
        break;
      case 2: // insert
        runInsert(T);
        break;
      case 3: // delete
        runDelete(T);
        break;
      case 4: // preorder
        T->preOrder(T->root, order);
        printVector(order);
        break;
      case 5: // inorder
        T->inOrder(T->root, order);
        printVector(order);
        break;
      case 6: // postorder
        T->postOrder(T->root, order);
        printVector(order);
        break;
      default:
        break;
    }
    cin >> operation;
  }

  return 0;
}

/*************************************************
 * Print the values of nodes in a vector         *
 * v - const vector<Node*> & - a vector of Nodes *
 * ***********************************************/
void printVector(const vector<Node*> &v){
  for (int i = 0; i < v.size(); i++){
    cout << v[i]->value << " ";
  }
  cout << endl;
}

/*******************************************************************************************
 * Given a BST, get a value to search for from the console and apply the BST search method *
 * T - BST* - a Binary Search Tree                                                         *
 * *****************************************************************************************/
void runSearch(BST* T){
  int target;
  cin >> target;
  Node* n = T->search(target);
  if (n){ cout << n->value << endl; }
  else{ cout << "Not found" << endl; }
}

/********************************************************************
 * Given a BST, get a value from the console and add it to the tree *
 * T - BST* - a Binary Search Tree                                  *
 * ******************************************************************/
void runInsert(BST* T){
  int newVal;
  cin >> newVal;
  T->insertValue(newVal);
}

/**************************************************************************************
 * Given a BST, get a value from the console and remove it from the tree if it exists *
 * T - BST* - a Binary Search Tree                                                    *
 * ************************************************************************************/
void runDelete(BST* T){
  int newVal;
  cin >> newVal;
  T->deleteValue(newVal);
}
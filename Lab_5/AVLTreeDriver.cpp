// CSCI 311 - Spring 2021
// Lab 5 - AVL Tree Driver
// Author: Carter Tillquist

#include <iostream>
#include <vector>
#include "AVLTree.h"
using namespace std;

void printVector(const vector<AVLNode*> &v);
void runSearch(AVLTree* T);
void runInsert(AVLTree* T);
void runDelete(AVLTree* T);

/****************************************
 * Simple main to test AVL Tree methods *
 * **************************************/
int main(){
  AVLTree* T = new AVLTree();

  int operation;
  cin >> operation;

  while (operation > 0){
    vector<AVLNode*> order;
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
        T->preOrder(T->getRoot(), order);
        printVector(order);
        break;
      case 5: // inorder
        T->inOrder(T->getRoot(), order);
        printVector(order);
        break;
      case 6: // postorder
        T->postOrder(T->getRoot(), order);
        printVector(order);
        break;
      case 7: // minimum
        cout << T->minimum()->value << endl;
        break;
      case 8: // maximum
        cout << T->maximum()->value << endl; 
        break;
      case 9: // size
        cout << T->getSize() << endl;
        break;
      default:
        break;
    }
    cin >> operation;
  }

  return 0;
}

/*******************************************************
 * Print the values of nodes in a vector               *
 * v - const vector<AVLNode*> & - a vector of AVLNodes *
 * *****************************************************/
void printVector(const vector<AVLNode*> &v){
  for (int i = 0; i < v.size(); i++){
    cout << v[i]->value << " ";
  }
  cout << endl;
}

/******************************************************************************************************
 * Given an AVL Tree, get a value to search for from the console and apply the AVL Tree search method *
 * T - AVLTree* - an AVLTree Tree                                                                     *
 * ****************************************************************************************************/
void runSearch(AVLTree* T){
  int target;
  cin >> target;
  AVLNode* n = T->search(target);
  if (n){ cout << n->value << endl; }
  else{ cout << "Not found" << endl; }
}

/**************************************************************************
 * Given an AVL Tree, get a value from the console and add it to the tree *
 * T - AVLTree* - an AVL Tree                                             *
 * ************************************************************************/
void runInsert(AVLTree* T){
  int newVal;
  cin >> newVal;
  T->insertValue(newVal);
}

/********************************************************************************************
 * Given an AVL Tree, get a value from the console and remove it from the tree if it exists *
 * T - AVLTree* - an AVL Tree                                                               *
 * ******************************************************************************************/
void runDelete(AVLTree* T){
  int newVal;
  cin >> newVal;
  T->deleteValue(newVal);
}
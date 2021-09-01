// CSCI 311 - Spring 2021
// Lab 4 - BST cpp skeleton
// Author: *** YOUR NAME HERE ***

#include<iostream>
#include <vector>
#include <limits.h>
#include "BST.h"
using namespace std;

BST::BST(){
   root = NULL;
   size = 0;
}

/*
This function checks if initial root is the search target requested
If not then we send it to the other search function adding the root Node
*/
Node* BST::search(int target) {
   if (isBST(root)) {
      if (root == NULL || root->value == target) {    //checks if empty or target is root
         return root;
      }
      else {
         return search(root, target);                 //calls the complex function if not root
      }
   }
   else {
      return nullptr;                                 //return null if tree is not BST
   }
}


/*
This functions checks appropriate node value to see if target exits or return null otherwise
*/
Node* BST::search(Node* n, int target) {
   if (n == NULL || n->value == target) {             //returns null or target as answer
      return n;
   }

   if (n->value > target) {                           //if current node value is greater than target
      return search(n->left, target);                 //we search left
   }
   else {
      return search(n->right, target);                //otherwise we search right
   }
}

/*
This functions checks if tree is BST and calls function to find min value
*/
Node* BST::minimum() {
   Node* curr = root;
   return minimum(curr);                             //calls function to find min value
}

/*
This fucntion finds the most left node for the minimum value
*/
Node* BST::minimum(Node* n) {

   if (n->left == NULL) {
      return n;                                       //returns the most left node possible
   }
   else {
      return minimum(n->left);
   }
   
}


/*
This functions checks if tree is BST and calls function to find max value
*/
Node* BST::maximum() {
   Node* curr = root;
   return maximum(curr);                              //calls function to find max value
}


/*
This fucntion finds the most right node for the maximum value
*/
Node* BST::maximum(Node* n) {
   if (n->right == NULL) {
      return n;                                       //returns the most right node possible
   }
   else {
      return maximum(n->right);
   }
   
}

/*
This function check root to see if valid or existent tree
*/
void BST::insertValue(int val) {
   if (root == NULL) {
      root = new Node(val);                           //if new tree then we add a new root Node and add the value
   }
   else if (isBST(root)) {
      insertValue(root, val);                         //checks if BST and sends current tree to add value
   }
}


/*
This function will pass through the appropriate nodes to see where the value has to be added
*/
void BST::insertValue(Node* n, int val) {
   
   if (val <= n->value)
   {
      if (n->left == NULL) {
         n->left = new Node(val);                  //inserts at left child
      }
      else {
         insertValue(n->left, val);                //iterates left
      }

   }
   else
   {
      if (n->right == NULL) {
         n->right = new Node(val);                 //inserts at right child
      }
      else {
         insertValue(n->right, val);               //iterates right
      }

   }
}



/*

This functions checks the initial value of tree for simple deletion

*/

void BST::deleteValue(int val) {

   if (root != NULL) {

      root = deleteValue(root, val);

   }

}


/*

Main element deletion function that deletes a provided value in the BST

*/

Node* BST::deleteValue(Node* n, int val) {

   if (n == NULL) {
      return n;
   }
   else if (n->value < val) {
      n->right = deleteValue(n->right, val);
   }
   else if (n->value > val) {
      n->left = deleteValue(n->left, val);
   }
   else {
      //Node* parent = n;

      if (n->left == NULL && n->right == NULL) {
         delete n;
         n = NULL; 
      }
      else if (n->left == NULL) {                  //Check for only sub right tree
         n = n->right; 
      }
      else if (n->right == NULL) {                 //Check for only left sub tree
         n = n->left;
      }
      else {                                            //If has both subtrees we will check the right side
         Node* temp = minimum(n->right);
         n->value = temp->value;
         n->right = deleteValue(n->right, n->value);
      }
      return n;
   }
   return n;
}


/*
checks basic detiails of tree to see if it is BST
*/
bool BST::isBST(Node* n) {
   if (n == NULL) {                                   //if root or node is null we have reached our end
      return true;
   }
   else if (n->left == NULL && n->right == NULL) {    //checks if only root exists
      return true;
   }
   else {
      return (isBST(n, minimum()->value, maximum()->value));   //we call other function for further inspection
   }
}


/*
We check if tree is BST given a lowest(min) and highest(max) points of tree
*/
bool BST::isBST(Node* n, int low, int high) {
   if (n == NULL) {
      return true;                                    //base case to check if node is NULL
   }
   if (n->value < low || n->value > high) {           //we check if node value is out of min/max bounds
      return false;
   }
   return isBST(n->left, low, n->value) && isBST(n->right, n->value, high);   //tighten the bounds to see if values still hold conditions
}


void BST::preOrder(Node* n, vector<Node*> &order){
   if (n != NULL) {
      order.push_back(n);                             //we add the value we find
      preOrder(n->left, order);                        //we traverse to the left and check if node is null to determine the end
      preOrder(n->right, order);                       //we traverse the right till node is null to determine the next value
   }
}

/*
Checks if empty list and prints out tree values sweeping from left to right
*/
void BST::inOrder(Node* n, vector<Node*>& order) {

   if (n != NULL) {
      inOrder(n->left, order);                        //we traverse to the left and check if node is null to determine the end
      order.push_back(n);                             //we add the value we find
      inOrder(n->right, order);                       //we traverse the right till node is null to determine the next value
   }
}

void BST::postOrder(Node* n, vector<Node*> &order){
   if (n != NULL) {
      postOrder(n->left, order);                        //we traverse to the left and check if node is null to determine the end
      postOrder(n->right, order);                       //we traverse the right till node is null to determine the next value
      order.push_back(n);                             //we add the value we find
   }

}
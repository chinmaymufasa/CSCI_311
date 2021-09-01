// CSCI 311 - Spring 2021
// Lab 5 Skeleton - AVLTree cpp
// Author: Carter Tillquist, Chinmay Satpanthi

#include<iostream>
#include <vector>
#include <limits.h>
#include "AVLTree.h"

using namespace std;

/*
AVL tree Node
*/
AVLTree::AVLTree() {
   root = NULL;            
   size = 0;
}

/*
Node root getter
*/
AVLNode* AVLTree::getRoot() {
   return root;
}

/*
Node size getter
*/
int AVLTree::getSize() {
   return size;
}

/*
search value in root
*/
AVLNode* AVLTree::search(int val) {

   if (root == NULL || root->value == val) {       //checks if empty or target is root
      return root;
   }
   else {
      return search(root, val);                    //calls the complex function if not root
   }
}

/*
search value in tree
*/
AVLNode* AVLTree::search(AVLNode* n, int val) {
   if (n == NULL || n->value == val) {             //returns null or target as answer
      return n;
   }
   if (n->value > val) {                           //if current node value is greater than target
      return search(n->left, val);                 //we search left
   }
   else {
      return search(n->right, val);                //otherwise we search right
   }
}
 
/*
Min function caller
*/
AVLNode* AVLTree::minimum() {
   return minimum(root);                          //calls function to find min value
}

/*
Min function
*/
AVLNode* AVLTree::minimum(AVLNode* n) {
   if (n->left == NULL) {
      return n;                                   //returns the most left node possible
   }
   else {
      return minimum(n->left);                    //iterates left
   }
}

/*
Max function caller
*/
AVLNode* AVLTree::maximum() {
   return maximum(root);                         //calls function to find max value
}

/*
Max function
*/
AVLNode* AVLTree::maximum(AVLNode* n) {
   if (n->right == NULL) {
      return n;                                  //returns the most right node possible
   }
   else {
      return maximum(n->right);                  //iterates right of tree
   }
}

/*
Height function
*/
int getHeight(AVLNode* n) {
   if (n != NULL) {
      int max_height = max(getHeight(n->left), getHeight(n->right));  //checks the height of left and right node and returns the max
      return max_height + 1;                                          //we return max plus one because its for previous node  
   }
   else {
      return 0;                                                       //Null will return 0
   }
}

/*
Balance function
*/
int getBalanceFactor(AVLNode* n) {
   if (n == NULL) {
      return 0;                                       //if null returns 0
   }
   return getHeight(n->right) - getHeight(n->left);   //return the height difference between the right and left node respectively 
}

/*
Insert value function at root or call other insert function
*/
void AVLTree::insertValue(int val) {
   if (root == NULL) {
      root = new AVLNode(val);                        //if new tree then we add a new root Node and add the value
      size++;
   }
   else {
      root = insertValue(root, val);                  //sends current tree to add value
      size++;
   }
}

/*
Insert value function
*/
AVLNode* AVLTree::insertValue(AVLNode* n, int val) {
   if (val <= n->value) {                             //left subtree
      if (n->left == NULL) {
         n->left = new AVLNode(val);                  //inserts at left child
         n->left->height = 0;                         //sets height to 0
         n->height = max(getHeight(n->left), getHeight(n->right)); //adjusts parent node's height
      }
      else {
         n->left = insertValue(n->left, val);        //iterates left
         n->height = max(getHeight(n->left), getHeight(n->right)); //adjusts parent node's height
         n = rebalance(n);
      }
   }
   else {
      
      if (n->right == NULL) {
         n->right = new AVLNode(val);              //inserts at right child
         n->right->height = 0;
         n->height = max(getHeight(n->left), getHeight(n->right)); //adjusts parent node's height
      }
      else {
         n->right = insertValue(n->right, val);   //iterates right
         n->height = max(getHeight(n->left), getHeight(n->right)); //adjusts parent node's height
         n = rebalance(n);
      }
   }
   return n;
}


/*
Delete value function check and caller
*/
void AVLTree::deleteValue(int val) {
   if (root != NULL) {
      if (search(val) != NULL) {             //checks if val is in tree
         root = deleteValue(root, val);      //calls the fucntion
         size--;
      }
   }
}

/*
Delete value function
*/
AVLNode* AVLTree::deleteValue(AVLNode* n, int val) {
   if (n == NULL) {
      return n;                              //returns null
   }
   else if (val < n->value) {                
      n->left = deleteValue(n->left, val);   //iterates left tree
      n = rebalance(n);                      
   }
   else if (val > n->value) {
      n->right = deleteValue(n->right, val); //iterates right
      n = rebalance(n);                      
   }
   else {                                    
      if (n->left == NULL && n->right == NULL) {   //deletes leaf node
         n->left = NULL;
         n->right = NULL;
         delete n;
         n = NULL;
      }
      else if (n->left == NULL) {         //sets n to right node
         AVLNode* temp = n;
         n = n->right;
         delete temp;
      }
      else if (n->right == NULL) {        //sets n to left node
         AVLNode* temp = n;
         n = n->left;
         delete temp;
      }
      else {                              //find the minimum of the right subtree and deletes the value
         AVLNode* temp = minimum(n->right);
         n->value = temp->value;
         n->right = deleteValue(n->right, temp->value);
      }
      n = rebalance(n);
   }
   return n;
}

/*
Rebalancing function
*/
AVLNode* AVLTree::rebalance(AVLNode* n) {

   if (getBalanceFactor(n) == 2 && getBalanceFactor(n->right) >= 0) {      //Right heavy tree
      return rotateLeft(n);                                                //rotates Left
   }
   else if (getBalanceFactor(n) == 2 && getBalanceFactor(n->right) < 0) {  //Right Mid heavy tree
      return rotateRightLeft(n);                                           //Rotates right at right subtree and left at parent node
   }
   else if (getBalanceFactor(n) == -2 && getBalanceFactor(n->left) <= 0) { //Left heavy tree
      return rotateRight(n);                                               //rotates right
   }
   else if (getBalanceFactor(n) == -2 && getBalanceFactor(n->left) > 0) {  //Left mid heavy tree
      return rotateLeftRight(n);                                           //Rotates left at left subtree and right at parent node
   }
   else {
      return n;                                                            //balanced will return same tree
   }
}


/*
Left rotation tree
*/
AVLNode* AVLTree::rotateLeft(AVLNode* n) {

   AVLNode* temp = n->right;                  //assignes temp the right subtree
   AVLNode* sub_tree = temp->left;            //assinges subtree the temp's left tree

   temp->left = n;                            //assignes the main tree to the left of the temp tree
   n->right = sub_tree;                       //assignes the saved subtree to the right of the n tree
   
   n->height = max(getHeight(n->left),getHeight(n->right));  //finds the height of the left subtree
   temp->height = n->height + 1;                             //the height of the temp tree
   
   return temp;                              //returns temp as it is the main tree 
}

/*
Right rotation tree
*/
AVLNode* AVLTree::rotateRight(AVLNode* n) {

   AVLNode* temp = n->left;                  //assignes temp the left subtree
   AVLNode* sub_tree = temp->right;          //assinges subtree the temp's right tree

   temp->right = n;                          //assignes the main tree to the right of the temp tree
   n->left = sub_tree;                       //assignes the saved subtree to the left of the n tree

   n->height = max(getHeight(n->left), getHeight(n->right)); //finds the height of the right subtree
   temp->height = n->height + 1;                             //the height of the temp tree

   return temp;                              //returns temp as it is the main tree 
}

/*
Left Right rotation tree
*/
AVLNode* AVLTree::rotateLeftRight(AVLNode* n) {
   n->left = rotateLeft(n->left);            //rotates the left subtree and assignes it back
   return rotateRight(n);                    //rotates right the parent node
}

/*
Right Left rotation tree
*/
AVLNode* AVLTree::rotateRightLeft(AVLNode* n) {
   n->right = rotateRight(n->right);         //rotates the right subtree and assignes it back
   return rotateLeft(n);                     //rotates left the parent node
}

/*
Pre order fucntion
*/
void AVLTree::preOrder(AVLNode* n, vector<AVLNode*>& order) {
   if (n != NULL) {
      order.push_back(n);                              //we add the value we find
      preOrder(n->left, order);                        //we traverse to the left and check if node is null to determine the end
      preOrder(n->right, order);                       //we traverse the right till node is null to determine the next value
   }
}

/*
In order function
*/
void AVLTree::inOrder(AVLNode* n, vector<AVLNode*>& order) {
   if (n != NULL) {
      inOrder(n->left, order);                        //we traverse to the left and check if node is null to determine the end
      order.push_back(n);                             //we add the value we find
      inOrder(n->right, order);                       //we traverse the right till node is null to determine the next value
   }
}

/*
Post order function
*/
void AVLTree::postOrder(AVLNode* n, vector<AVLNode*>& order) {
   if (n != NULL) {
      postOrder(n->left, order);                        //we traverse to the left and check if node is null to determine the end
      postOrder(n->right, order);                       //we traverse the right till node is null to determine the next value
      order.push_back(n);                               //we add the value we find
   }
}


// CSCI 311 - Spring 2021
// Lab 5 Skeleton - AVLTree cpp
// Author: Carter Tillquist

#include<iostream>
#include <vector>
#include <limits.h>
#include "AVLTree.h"

using namespace std;


AVLTree::AVLTree() {
   root = NULL;
   size = 0;

}

AVLNode* AVLTree::getRoot() {
   return root;
}

int AVLTree::getSize() {
   return size;
}

AVLNode* AVLTree::search(int val) {

   if (root == NULL || root->value == val) {    //checks if empty or target is root
      return root;
   }
   else {
      return search(root, val);                 //calls the complex function if not root
   }
}

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

AVLNode* AVLTree::minimum() {
   return minimum(root);                             //calls function to find min value
}

AVLNode* AVLTree::minimum(AVLNode* n) {
   if (n->left == NULL) {
      return n;                                       //returns the most left node possible
   }
   else {
      return minimum(n->left);
   }
}

AVLNode* AVLTree::maximum() {
   return maximum(root);                              //calls function to find max value
}

AVLNode* AVLTree::maximum(AVLNode* n) {
   if (n->right == NULL) {
      return n;                                       //returns the most right node possible
   }
   else {
      return maximum(n->right);
   }
}

int getHeight(AVLNode* n) {
   int temp_height = 0;
   if (n != NULL) {
      int temp_left = getHeight(n->left);
      int temp_right = getHeight(n->right);
      int max_height = max(temp_left, temp_right);
      temp_height = max_height + 1;
   }
   else {
      return 0;
   }
   return temp_height;
}

int getBalanceFactor(AVLNode* n) {
   if (n == NULL) {
      return 0;
   }
   int temp_left = getHeight(n->left);
   int temp_right = getHeight(n->right);
   return temp_right - temp_left;
}

void AVLTree::insertValue(int val) {
   if (root == NULL) {
      root = new AVLNode(val);                           //if new tree then we add a new root Node and add the value
      size++;
   }
   else {
      root = insertValue(root, val);                         //checks if BST and sends current tree to add value
      size++;
   }
}

AVLNode* AVLTree::insertValue(AVLNode* n, int val) {
   if (n == NULL) {
      n = new AVLNode(val);
      n->height = 0;
   }
   else if (val <= n->value) {
      
      if (n->left == NULL) {
         n->left = new AVLNode(val);               //inserts at left child
         n->left->height = 0;
         n->height = max(getHeight(n->left), getHeight(n->right));
      }
      else {
         n->left = insertValue(n->left, val);            //iterates left
         n->height = max(getHeight(n->left), getHeight(n->right));
         n = rebalance(n);
      }
   }
   else {
      
      if (n->right == NULL) {
         n->right = new AVLNode(val);              //inserts at right child
         n->right->height = 0;
         n->height = max(getHeight(n->left), getHeight(n->right));
      }
      else {
         n->right = insertValue(n->right, val);           //iterates right
         n->height = max(getHeight(n->left), getHeight(n->right));
         n = rebalance(n);
      }
   }
   return n;
}

void AVLTree::deleteValue(int val) {
   if (root != NULL) {
      if (search(val) != NULL) {
         root = deleteValue(root, val);
         size--;
      }
   }
}

AVLNode* AVLTree::deleteValue(AVLNode* n, int val) {
   if (n == NULL) {
      return n;
   }
   else if (val < n->value) {
      n->height -= 1;
      n->left = deleteValue(n->left, val);
      n = rebalance(n);
   }
   else if (val > n->value) {
      n->height -= 1;
      n->right = deleteValue(n->right, val);
      n = rebalance(n);
   }
   else {
      if (n->left == NULL && n->right == NULL) {
         n->left = NULL;
         n->right = NULL;
         delete n;
         n = NULL;
      }
      else if (n->left == NULL) {
         AVLNode* temp = n;
         n = n->right;
         delete temp;
      }
      else if (n->right == NULL) {
         AVLNode* temp = n;
         n = n->left;
         delete temp;
      }
      else {
         AVLNode* temp = minimum(n->right);
         n->value = temp->value;
         n->right = deleteValue(n->right, temp->value);
      }
      n = rebalance(n);
   }
   return n;
}

AVLNode* AVLTree::rebalance(AVLNode* n) {

   if (getBalanceFactor(n) == 2 && getBalanceFactor(n->right) >= 0) {
      return rotateLeft(n);
   }
   else if (getBalanceFactor(n) == 2 && getBalanceFactor(n->right) < 0) {
      return rotateRightLeft(n);
   }
   else if (getBalanceFactor(n) == -2 && getBalanceFactor(n->left) <= 0) {
      return rotateRight(n);
   }
   else if (getBalanceFactor(n) == -2 && getBalanceFactor(n->left) > 0) {
      return rotateLeftRight(n);
   }
   else {
      return n;
   }
}

AVLNode* AVLTree::rotateLeft(AVLNode* n) {

   AVLNode* temp = n->right;
   AVLNode* sub_tree = temp->left;

   temp->left = n;
   n->right = sub_tree;
   
   n->height = max(getHeight(n->left),getHeight(n->right));
   temp->height = n->height + 1;
   return temp;
}

AVLNode* AVLTree::rotateRight(AVLNode* n) {

   AVLNode* temp = n->left;
   AVLNode* sub_tree = temp->right;

   temp->right = n;
   n->left = sub_tree;

   n->height = max(getHeight(n->left), getHeight(n->right));
   temp->height = n->height + 1;
   return temp;
}

AVLNode* AVLTree::rotateLeftRight(AVLNode* n) {
   n->left = rotateLeft(n->left);
   return rotateRight(n);
}

AVLNode* AVLTree::rotateRightLeft(AVLNode* n) {
   n->right = rotateRight(n->right);
   return rotateLeft(n);
}

void AVLTree::preOrder(AVLNode* n, vector<AVLNode*>& order) {
   if (n != NULL) {
      order.push_back(n);                             //we add the value we find
      preOrder(n->left, order);                        //we traverse to the left and check if node is null to determine the end
      preOrder(n->right, order);                       //we traverse the right till node is null to determine the next value
   }
}

void AVLTree::inOrder(AVLNode* n, vector<AVLNode*>& order) {
   if (n != NULL) {
      inOrder(n->left, order);                        //we traverse to the left and check if node is null to determine the end
      order.push_back(n);                             //we add the value we find
      inOrder(n->right, order);                       //we traverse the right till node is null to determine the next value
   }
}

void AVLTree::postOrder(AVLNode* n, vector<AVLNode*>& order) {
   if (n != NULL) {
      postOrder(n->left, order);                        //we traverse to the left and check if node is null to determine the end
      postOrder(n->right, order);                       //we traverse the right till node is null to determine the next value
      order.push_back(n);                             //we add the value we find
   }
}


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
   if (n != NULL) {
      int temp_left = getHeight(n->left);
      int temp_right = getHeight(n->right);
      int max_height = max(temp_left, temp_right);
      return max_height + 1;
   }
   else {
      return 0;
   }
}

int getBalanceFactor(AVLNode* n) {
   int temp_left = getHeight(n->left);
   int temp_right = getHeight(n->right);
   return temp_right - temp_left;
}

void AVLTree::insertValue(int val) {
   if (root == NULL) {
      root = new AVLNode(val);                           //if new tree then we add a new root Node and add the value
   }
   else {
      root = insertValue(root, val);                         //checks if BST and sends current tree to add value
      size++;
   }
}

AVLNode* AVLTree::insertValue(AVLNode* n, int val) {
   if (n == null) {
      n = new AVLNode(val);
      n->height = 0;
   }
   else if (val <= n->value) {
      if (n->left == NULL) {
         n->left = new AVLNode(val);               //inserts at left child
         n->height = 0;
      }
      else {
         n = insertValue(n->left, val);            //iterates left
         n = rebalance(n);
      }
   }
   else {
      if (n->right == NULL) {
         n->right = new AVLNode(val);              //inserts at right child
         n->height = 0;
      }
      else {
         n = insertValue(n->right, val);               //iterates right
         n = rebalance(n);
      }
   }
   return n;
}

void AVLTree::deleteValue(int val) {
   if (root != NULL) {
      if (search(val)) {
         deleteValue(root, val);
         size--;
      }
      else {
         deleteValue(root, val);
      }
   }
}

AVLNode* AVLTree::deleteValue(AVLNode* n, int val) {
   if (n == NULL) {
      return n;
   }
   else if (val < n->value) {
      n->left = deleteValue(n->left, val);
      n = rebalance(n);
   }
   else if (val > n->value) {
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
   return root;
}

AVLNode* AVLTree::rebalance(AVLNode* n) {
   if (n->balanceFactor == 2 && n->right->balanceFactor >= 0) {
      return rotateLeft(n);
   }
   else if (n->balanceFactor == 2 && n->right->balanceFactor < 0) {
      return rotateRightLeft(n);
   }
   else if (n->balanceFactor == -2 && n->left->balanceFactor <= 0) {
      return rotateRight(n);
   }
   else if (n->balanceFactor == -2 && n->left->balanceFactor > 0) {
      return rotateLeftRight(n);
   }
   else {

      return n;
   }
}

AVLNode* AVLTree::rotateLeft(AVLNode* n) {
   AVLNode* temp = new AVLNode(n);
   if (temp->left == NULL) {
      temp->left = insertValue(temp->left, temp->value);
      if (temp->right->left != NULL) {
         temp->left->right = temp->right->left;
         temp->left->height = max(getHeight(temp->left), getHeight(temp->left->right));
      }
      else {
         temp->left->height = 0;
      }
   }
   else {
      AVLNode* temp_left = new AVLNode(temp->left);
      temp->left = insertValue(temp->left, temp->value);
      if (temp->right->left != NULL) {
         temp->left->right = temp->right->left;
      }
      temp->left->left = temp_left;
      temp->left->height = max(getHeight(temp->left->left), getHeight(temp->left->right));
   }
   n = n->right;
   n->left = temp->left;
   n->height = max(getHeight(n->left), getHeight(n->right));
   delete temp;
   return n;
}

AVLNode* AVLTree::rotateRight(AVLNode* n) {
   AVLNode* temp = new AVLNode(n);
   if (temp->right == NULL) {
      temp->right = insertValue(temp->right, temp->value);
      if (temp->left->right != NULL) {
         temp->right->left = temp->left->right;
         temp->right->height = max(getHeight(temp->right), getHeight(temp->right->left));
      }
      else {
         temp->right->height = 0;
      }
   }
   else {
      AVLNode* temp_right = new AVLNode(temp->right);
      temp->right = insertValue(temp->right, temp->value);
      if (temp->left->right != NULL) {
         temp->right->left = temp->left->right;
      }
      temp->right->right = temp_right;
      temp->right->height = max(getHeight(temp->right->right), getHeight(temp->right->left));
   }
   n = n->left;
   n->right = temp->right;
   n->height = max(getHeight(n->left), getHeight(n->right));
   delete temp;
   return n;
}

AVLNode* AVLTree::rotateLeftRight(AVLNode* n) {
   n = rotateLeft(n->left);
   return rotateRight(n);
}

AVLNode* AVLTree::rotateRightLeft(AVLNode* n) {
   n = rotateRight(n->right);
   return rotateLeft(n);
}

void AVLTree::preOrder(AVLNode* n, vector<AVLNode*>& order) {
   if (n != NULL) {
      order.push_back(n);                             //we add the value we find
      inOrder(n->left, order);                        //we traverse to the left and check if node is null to determine the end
      inOrder(n->right, order);                       //we traverse the right till node is null to determine the next value
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
      inOrder(n->left, order);                        //we traverse to the left and check if node is null to determine the end
      inOrder(n->right, order);                       //we traverse the right till node is null to determine the next value
      order.push_back(n);                             //we add the value we find
   }
}


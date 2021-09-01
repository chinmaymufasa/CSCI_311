// CSCI 311 - Spring 2021
// Lab 3 Solution - BST cpp skeleton
// Author: *** YOUR NAME HERE ***

#include<iostream>
#include <vector>
#include <limits.h>
#include "BST.h"
using namespace std;



BST::BST()
{
   root = NULL;
   size = 0;
}

Node* BST::search(int target){
   if (isBST(root)) {
      if (root == NULL || root->value == target) {
         return root;
      }
      else search(root, target);
   }
   else
      return nullptr;
}

Node* BST::search(Node* n, int target){
   if (n == NULL || n->value == target) {
      return n;
   }

   if (n->value > target) {
      return search(n->left, target);
   }
   else {
      return search(n->right, target);
   }
}

Node* BST::minimum(){
   Node* current = root;
   return minimum(current);
}

Node* BST::minimum(Node* n){
   if (n->left == NULL) {
      return n;
   }
   minimum(n->left);
}

Node* BST::maximum(){
   Node* current = root;
   return maximum(current);
}

Node* BST::maximum(Node* n){
   if (n->right == NULL) {
      return n;
   }
   maximum(n->right);
}

void BST::insertValue(int val){
   if (root == NULL) {
      root = new Node(val);
   }
   else {
      insertValue(root, val);
   }
}

void BST::insertValue(Node* n, int val){
   // Insert data.
   if (val >= n->value)
   {
      if (n->right == NULL) {
         n->right = new Node(val);
      }
      else {
         insertValue(n->right, val);
      }
   }
   else
   {
      if (n->left == NULL) {
         n->left = new Node(val);
      }
      else {
         insertValue(n->left, val);
      }
      
   }
   
}

void BST::deleteValue(int val){
}

void BST::deleteValue(Node* n, int val){
}

bool BST::isBST(Node* n){
   if (n == NULL) {
      return true;
   }
   else if (n->left == NULL && n->right == NULL) {
      return true;
   }
   else {
      return (isBST(n, minimum()->value, maximum()->value));
   }
}

bool BST::isBST(Node* n, int low, int high){
   if (n == NULL) {
      return true;
   }
   if (n->value < low || n->value > high) {
      return false;
   }
   return isBST(n->left, low, n->value) && isBST(n->right, n->value, high);
}

void BST::preOrder(Node* n, vector<Node*> &order){
   
}

void BST::inOrder(Node* n, vector<Node*> &order){
   if (n != nullptr) {
      inOrder(n->left, order);
      order.push_back(n);
      inOrder(n->right, order);
   }
}

void BST::postOrder(Node* n, vector<Node*> &order){
}
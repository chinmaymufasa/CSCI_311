// CSCI 311 - Spring 2021
// Exam 2
// Author: Chinmay Satpanthi

#include <iostream>
#include <vector>
#include <string>
#include "BST.h"
#include "HashTable.h"
using namespace std;


/**********************************************************************
 * QUESTION 1                                                         *
 * Write a function that, given a node of a BST, inverts its subtree. *
 * This function should return the root of the new substree           *
 * ********************************************************************/
Node* invertBST(Node* v) {
   
   Node *temp;

   if (v == NULL) {
      return NULL;            //base case
   }
   else {
      invertBST(v->left);     //get to left side of tree
      invertBST(v->right);    //recurse right side of tree
      
      temp = v->left;         //flip the left and right node
      v->left = v->right;
      v->right = temp;
   }
   return v;                  //return vector
}

/********************************************************************************************
 * QUESTION 2                                                                               *
 * Write a function that returns true if the given vector is a min-heap and false otherwise *
 * ******************************************************************************************/
bool isMinHeap(const vector<int>& v) {
   
   int v_size = v.size();
   
   for (int i = 0; i <= (v_size - 2)/ 2; i++) {      //for all values in the parent node range
      if (v[2 * i + 1] < v[i] ) {                    //checks if left node is less than parent 
         return false;
      }
      else if (v[2 * i + 2] < v[i]) {                //checks if right node is less than parent 
         return false;
      }
   }  
   return true;                                      //if no child nodes are less than parent its a min heap
}

/****************************************************************************
 * QUESTION 3                                                               *
 * Use the maxHeapify and pop functions below to write a heapsort function. *
 * It might be worthwhile to implement a constructMaxHep function as well.  *
 * **************************************************************************/

 /**************************************************************************************
  * Given a vector that represents a max-heap where a single value at index i might be *
  * out of order, rearrange the values so the vector is a true max-heap                *
  * v - vector<int>& - the vector representing a max-heap                              *
  * i - int - the index of the value that may be out of order                          *
  * heapSize - int - the size of the heap. Note that this may be < v.size()            *
  * ************************************************************************************/
void maxHeapify(vector<int>& v, int i, int heapSize) {
   int left = 2 * i + 1;
   int right = 2 * i + 2;
   int maxI = i;
   if (left < heapSize && v[left] > v[i]) { maxI = left; }
   if (right < heapSize && v[right] > v[maxI]) { maxI = right; }
   if (maxI != i) {
      int temp = v[i];
      v[i] = v[maxI];
      v[maxI] = temp;
      maxHeapify(v, maxI, heapSize);
   }
}

/***************************************************************************
 * Remove and return the maximum value of a max-heap                       *
 * v - vector<int>& - a max-heap                                           *
 * heapSize - int - the size of the heap. Note that this may be < v.size() *
 * *************************************************************************/
int pop(vector<int>& v, int heapSize) {
   int max = v[0];
   v[0] = v[heapSize - 1];
   maxHeapify(v, 0, heapSize - 1);
   return max;
}

/*
Max heap helper function
*/
void constructMaxHeap(vector<int>& v)
{
   for (int i = (v.size() / 2); i >= 0; i--){      //re heapifies the vector as max to get the true max-heap vector
      maxHeapify(v, i, v.size());
   }
}


/*
Heap sort function
*/
void heapsort(vector<int>& v)
{
   constructMaxHeap(v);                         //calls the reheapify helper function to set the vector to true max
   int vector_size = v.size();

   for (int i = v.size() - 1; i > 0; i--)       //check the values in vector and swap the sorted values from vector values
   {
      swap(v[0], v[i]);
      vector_size--;
      maxHeapify(v, 0, vector_size);
   }
}

/***********************************************************************************
 * QUESTION 4                                                                      *
 * Write a function to determine whether or not vector A is a subset of vector B.  *
 * You may assume that these vectors represent sets. In particular, you may ignore *
 * duplicate values.                                                               *
 * *********************************************************************************/
bool isSubset(const vector<string>& A, const vector<string>& B) {
   
   if (A.size() <= B.size()) {

      for (int i = 0; i <= B.size() - A.size(); i++) {         //for all character other than last pattern string length
         if (B[i] == A[0]) {
            for (int j = 0; j < A.size(); j++) {
               if (j == A.size() && B[i + j] == A[j]) {        //checks if the letters of the string are same
                  return true;
               }
               if (B[i + j] != A[j]) {                         //continues if no match
                  break;
               }
               
            }
         }
      }
   }
   else if (A.size() > B.size()) {
      for (int i = 0; i <= A.size() - B.size(); i++) {         //is the A vector is larger than the B vector
         if (A[i] == B[0]) {
            for (int j = 0; j < B.size(); j++) {
               if (j == B.size() && A[i + j] == B[j]) {        //checks the letters
                  return true;
               }
               if (A[i + j] != B[j]) {                         //continues if no match
                  break;
               }

            }
         }
      }
   }

   return false;
}



/********************************************************************************************************
 * TESTING                                                                                              *
 * When testing your functions, the main below expects input in a certain format for each question.     *
 * The first line of input should always the question number (1-4). More details are provided regarding *
 * the input for each question in the main itself.                                                      *
 * To test, you may run program and provide input by hand or you may provide a file as input directly   *
 * from the terminal For example, suppose you compile your program to a.out and that you have a file    *
 * named "test_1.in" containing input in the appropriate format for question 1. Then running            *
 * ./a.out < test_1.in                                                                                  *
 * will run your program using the lines of test_1.in as input. This can be a good way to save time and *
 * to save different test cases when testing your code.                                                 *
 * ******************************************************************************************************/
void readIntVector(vector<int>& v, int n);
void readStringVector(vector<string>& v, int n);
int main() {
   int question = -1;
   cin >> question;

   //Declaring variables to use in the switch
   int n = -1, m = -1;
   vector<int> v;
   vector<string> A;
   vector<string> B;
   vector<Node*> order;

   switch (question) {
   case 1: { // invert BST
     /***********************************
      * Input format:                   *
      * 1                               *
      * the number of nodes in the tree *
      * integers to include in the tree *
      * *********************************/
      cout << "INVERTBST" << endl;
      cin >> n;
      readIntVector(v, n);
      BST* T = new BST(v);
      invertBST(T->root);
      T->preOrder(T->root, order);
      cout << "PREORDER: ";
      for (int i = 0; i < order.size() - 1; i++) {
         cout << order[i]->value << ", ";
      }
      cout << order[order.size() - 1]->value << endl;
      break;
   }
   case 2: { // is min-heap
     /**************************
      * Input format:          *
      * 2                      *
      * number of elements     *
      * integers in the vector *
      * ************************/
      cout << "ISMINHEAP" << endl;
      cin >> n;
      readIntVector(v, n);
      cout << isMinHeap(v) << endl;
      break;
   }
   case 3: { // heapsort
     /**************************
      * Input format:          *
      * 3                      *
      * number of elements     *
      * integers in the vector *
      * ************************/
      cout << "HEAPSORT" << endl;
      cin >> n;
      readIntVector(v, n);
      heapsort(v);
      for (int i = 0; i < v.size() - 1; i++) {
         cout << v[i] << ", ";
      }
      cout << v[v.size() - 1] << endl;
      break;
   }
   case 4: { // is sub(multi)set
     /*******************************************
      * Input format:                           *
      * 4                                       *
      * number of elements in the first vector  *
      * strings in the first vector             *
      * number of elements in the second vector *
      * strings in the second vector            *
      * *****************************************/
      cout << "ISSUBSET" << endl;
      cin >> n;
      readStringVector(A, n);
      cin >> m;
      readStringVector(B, m);
      cout << isSubset(A, B) << endl;
      break;
   }
   default:
      break;
   }

   return 0;
}

/**************************************************
 * Read a vector of integers in from cin          *
 * v - vector<int> & - the integer vector to fill *
 * n - int - the number of integers to read       *
 * ************************************************/
void readIntVector(vector<int>& v, int n) {
   int m = 0;
   for (int i = 0; i < n; i++) {
      cin >> m;
      v.push_back(m);
   }
}

/****************************************************
 * Read a vector of strings in from cin             *
 * v - vector<string> & - the string vector to fill *
 * n - int - the number of strings to read          *
 * **************************************************/
void readStringVector(vector<string>& v, int n) {
   string m = "";
   for (int i = 0; i < n; i++) {
      cin >> m;
      v.push_back(m);
   }
}
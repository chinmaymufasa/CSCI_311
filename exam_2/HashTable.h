// CSCI 311 - Spring 2021
// Exam 2 Hash Table header
// Author: Carter Tillquist

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <string> 
using namespace std;

class HashTable {
public:
   HashTable();
   HashTable(int, int);

   int search(string);
   void insert(string);

   int getSize();
   int getNumElements();
   int getP();

private:
   int size;
   int numElements;
   int p;
   vector<vector<string>> table;

   int hash(string);
};

#endif
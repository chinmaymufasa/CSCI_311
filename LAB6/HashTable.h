// CSCI 311 - Spring 2021
// Lab 6 Hash Table header
// Author: Carter Tillquist

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
using namespace std;

class HashTable{
  public:
    HashTable();
    HashTable(int, int);

    int search(string);
    void insert(string);
    void remove(string);
    void resize(int);

    int getSize();
    int getNumElements();
    int getP();

    void printTable();

  private:
    int size;
    int numElements;
    int p;
    vector<vector<string>> table;

    int hash(string);
};

#endif
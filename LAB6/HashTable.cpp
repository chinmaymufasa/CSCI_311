// CSCI 311 - Spring 2021
// Lab 6 - Hash Table cpp
// Author: Carter Tillquist, Chinmay Satpanthi

#include <iostream>
#include <vector>
#include <list>
#include <math.h>
#include "HashTable.h"


/*
Deafult constructor with no args
default size= 11
default p = 31
initialize table;
*/
HashTable::HashTable(){
   numElements = 0;
   size = 11;
   p = 31;
   table.resize(11);
}

/*
Constructor with specfic arguments
table initialize accordingly
*/
HashTable::HashTable(int s, int mult){
   size = s;
   p = mult;
   numElements = 0;
   table.resize(s);
}

/*
table size getter function
*/
int HashTable::getSize(){
   return size; 
}

/*
gets the number of elements in table
*/
int HashTable::getNumElements(){
   return numElements; 
}

/*
gets the p value
*/
int HashTable::getP(){
   return p; 
}

/*
prints the current content in the hash table
*/
void HashTable::printTable(){
  cout << "HASH TABLE CONTENTS" << endl;
  for (unsigned int i = 0; i < table.size(); i++){
    if (table[i].size() > 0){
      cout << i << ": ";
      for (unsigned int j = 0; j < table[i].size()-1; j++){
        cout << table[i][j] << ", ";
      }
      cout << table[i][table[i].size()-1] << endl;
    }
  }
}


/*
Searches for given string in hash table
*/
int HashTable::search(string s){
   
   int index = hash(s);                  //gets the hash value
   for (unsigned int i = 0; i < table[index].size(); i++) { //looks for populated hash index
      if (table[index][i] == s){
         return index;                  //returs if found else returns -1
      }
   }
   return -1;
}

/*
Insert function, inserts string s into hash table
*/
void HashTable::insert(string s){
   printf("test1 \n");
   unsigned int index = hash(s);       //finds the hash index
   table[index].push_back(s);          //places the string in the index vector
   numElements++;                      //increments the number of elements
}


/*
Remove function, removes the string provided if found
*/
void HashTable::remove(string s){
   int hash_value = hash(s);           //finds the hash value
   for (unsigned int i = 0; i < table[hash_value].size(); i++) {  //checks all the string at hash index for string
      if (table[hash_value][i] == s) { //compares to string
         table[hash_value].erase(table[hash_value].begin() + i);  //removes element
         numElements--;                //decrements number of elementss
         break;
      }
   }
   
}


/*
Resize function, resizes the table and rehases all the values in it
*/
void HashTable::resize(int s){

   vector<string> H_strings;        //value storage vector
   for (unsigned int i = 0; i < table.size(); i++) {        //goes through all values of table
      if (table[i].size() > 0) {
         for (unsigned int j = 0; j < table[i].size(); j++) {
            H_strings.push_back(table[i][j]);               //adds string to the storage vector
         }
      }
   }
   table.clear();                   //clears out table
   table.resize(s);                 //reinitializes table
   size = s;                        //sets the new size of table

   for (unsigned int i = 0; i < H_strings.size(); i++) {
      unsigned int index = hash(H_strings[i]);  //rehashes the strings
      table[index].push_back(H_strings[i]);     //places them back into the table
   }

}

/*
Hash function, finds the hash value of string
*/
int HashTable::hash(string s){
   printf("test \n");
   long long int power_value = 0;             //power variable
   unsigned long long hash_value = 0;     //hash value variable
   for (unsigned int i = 0; i < s.length(); i++) {       //for all the character in string
      hash_value += int(s[i]) * pow(getP(),power_value); //ASCII value * p value ^ (ith number)
      power_value++;                                     //incremetns p value
      printf("test \n");
      printf("%llu \n", hash_value);
   }
                                             //returns unsigned int value so no negatives
   return hash_value % getSize();
}
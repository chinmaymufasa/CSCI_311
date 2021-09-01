// CSCI 311 - Spring 2021
// Lab 2
// Author: Chinmay Satpanthi

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

/*
This function calculates the triangle number of the provided integer n
*/
int triangleNum(int n) {
   if (n == 1) {                                   //checks if input was simply one, if so returns 1
      return 1;                                       
   }
   return triangleNum(n - 1) + n;                  //adds previous value to n-1: calls the function till n decrements to 1
}


/*
This function returns the nth fibonacci number 
*/
int rFib(int n) {
   if (n == 0) {                                   //n == 0 case returns 0
      return 0;

   }
   else if (n == 1) {                              //n == 1 case returns 1
      return 1;
   }
   return rFib(n - 1) + rFib(n - 2);               //this add the two function with the two next numbers for the fibonacci sequence
}


/*
This helper-function returns the sum of all the values in the vector given i = 1
*/
int rSumHelper(const vector<int>& v, int i) {
   if (i >= v.size() - 1) {                        //this is the base case that returns the last number when reaching at the end of vector          
      return v[i];
   }
   return v[i] + rSumHelper(v, i + 1);             //we add the number at i in the vetor plus the next number in the vector

}

/*
This function returns the sum of all the values in the vector
*/
int rSum(const vector<int>& v) {
   if (v.size() == 0) {                            //base case test to see if vector is empty
      return 0;
   }
   if (v.size() == 1) {                            //checks if vector is size one then the sum is the only value
      return v[0];
   }
   return  v[0] + rSumHelper(v, 1);                //adds the first value since we are not calling it witht the sum from the helper function
}


/*
This function helps find the max in the vector provided
*/
int rMaxHelper(const vector<int>& v, int i, int max) {
   if (i >= v.size()) {                             //checks to see of base case has reached at the end of vector
      return max;                                   
   }
   if (v[i] >= max) {                               //if the current value is greater than the max then we call in the function with the new max

      return rMaxHelper(v, i+1, v[i]);
   }
   else
      return rMaxHelper(v, i+1, max);               //if the current value is less that the max then we iterate to the vector value
}


/*
This functins finds the max value in the vector provided 
*/
int rMax(const vector<int>& v) {    
   if (v.empty()) {                                //checks foir empty vector, if so returns INT_MIN
      return INT_MIN;
   }
   if (v.size() == 0) {                            //if empty vector then we return 0
      return 0;
   }
   if (v.size() == 1) {                            //if vector size is 1 then we return the only value available
      return v[0];
   }
   return rMaxHelper(v, 1, v[0]);                  //calls the helper function with an initial integer and a max option
}


/*
This function checks if the vector is sorted 
*/
bool isSorted(const vector<int>& v, int start, int end) {
   if (start > end) {                              //checks to see if we have any odd cases
      return false;
   }
   if (v.size() == 1 || start == end || v.size() == 0) {  //checks all the statements to see if all requirements matchs
      return true;
   }
   if (v[start] < v[end]) {                        //Here we checks to see if we still have not completed the iteration
      return isSorted(v, start + 1, end);          //if not complete we call the function again with incrementing index
   }
   if (v[start] > v[end]) {                        //if any of the values before the right side is greater we return false
      return false;
   }
}


/*
This function will do the checks to see if the string provided is a palindrome
*/
bool isPalindromeHelper(string s, int left, int right) {
   if (right <= left) {                            //if we reach to the middle without exiting we return true that it is a palindrome
      return true; 
   }
   if (s[left] == s[right]) {                      //checks the letter on both sides to see if they match
      return isPalindromeHelper(s, left + 1, right - 1); //if they do we increment inwards 
   }
   else {
      return false;                                //if no match we return false 
   }
}


/*
This function calls in the string and checks basic limits and sends the values to the helper function
*/
bool isPalindrome(string s) {
   if (s.length() == 0) {                          //if the length is 0 then the string is empty
      return false;
   }
   if (s.length() == 1) {                          //if the lenght is 1 then it is a palindrome
      return true;
   }
   return isPalindromeHelper(s, 0, s.length() - 1);   //call the palindrom helper function with string, start length and end 
}

/*
This function looks for a value in the vector with a low and a high value
*/
int rBinarySearch(const vector<int>& v, int low, int high, int target) {

   if (high >= 0) {                                          //checks for no negatives in the vector indexes  
      if (target > v[high] || target < v[low]) {             //this checks if the target is out of range
         return -1;
      }
      if (v.size() == 1) {                                   //if the size of the vector is 1 then we check the only value
         if (v[0] == target) {                               //if the only value is also the target we return true
            return 0;
         }
         else {
            return - 1;                                      //else we return false 
         }
      }
      int mid = low + ((high - low) / 2);                    //this will calculate the midpoint of the low and high

      if (v[mid] > target) {                                 //if the value at mid is greater the we look at the bottom half
         return rBinarySearch(v, low, mid - 1, target);      //we set the new high value to the mid value
      }
      else if (v[mid] == target) {                           //checks if the mid value is the target
         return mid;
      }
      else
         return rBinarySearch(v, mid + 1, high, target);     //this calls the function if the the target is greater than mid then we look at the top half
   }
   else {
      return - 1;                                            //if none of the cases match it means there is no target in the vector
   }
   

}



/*
This helper function checks all the possibilities of the subsets by checking of the possibility with or without the element
*/
bool rSubsetSumHelper(const vector<int>& v, int size, int target) {
   if (target == 0) {                                                  //if we have reached the target then we know there is a sum
      return true;
   }
   if (size == 0 && target != 0) {                                     //if we have gone through all the possibilities and no sum, then we return false
      return false;
   }

   if (v[size - 1] > target) {                                         //if we have not yet reached the target we call the function again
      return rSubsetSumHelper(v, size - 1, target);
   }
   return rSubsetSumHelper(v, size - 1, target) || rSubsetSumHelper(v, size - 1, target - v[size - 1]);  //this checks if we should include the last element or not
}


/*
This function checks the basic cases to see if the vector is active and populated
*/
bool rSubsetSum(const vector<int>& v, int start, int target) {
   if (v.size() == 0) {                                              //if the vector is empty then we return false
      return false;
   }
   if (v.size() == 1 && v[0] == target) {                            //if size of the vector is 1 and value is the target we return true
      return true;
   }
   if (v.size() == 1 && v[0] != target) {                            //else if vector at index 1 is not the same value of the target we return false
      return false;
   }
   return rSubsetSumHelper(v, v.size(), target);                     //we call the function if all the cases and conditions look good

}

/***********************************************
 * Main and helper functions for quick testing *
 * *********************************************/
void readIntVector(vector<int>& v, int n);

int main() {
   int question = -1;
   cin >> question;

   int n = 0, start = 0, end = 0;
   vector<int> v;
   string s = "";
   cin >> n;
   switch (question) {
   case 1: //triangleNum
      cout << triangleNum(n) << endl;
      break;
   case 2: //rFib
      cout << rFib(n) << endl;
      break;
   case 3: //rSum
      readIntVector(v, n);
      cout << rSum(v) << endl;
      break;
   case 4: //rMax
      readIntVector(v, n);
      cout << rMax(v) << endl;
      break;
   case 5: //isSorted
      cin >> start >> end;
      readIntVector(v, n);
      cout << isSorted(v, start, end) << endl;
      break;
   case 6: //isPalindrome
      cin.clear();
      cin >> s;
      cout << isPalindrome(s) << endl;
      break;
   case 7: //rBinarySearch
      cin >> end;
      readIntVector(v, n);
      cout << rBinarySearch(v, 0, v.size() - 1, end) << endl;
      break;
   case 8: //rSubsetSum
      cin >> end;
      readIntVector(v, n);
      cout << rSubsetSum(v, 0, end) << endl;
      break;
   }

   return 0;
}

void readIntVector(vector<int>& v, int n) {
   int m = 0;
   for (int i = 0; i < n; i++) {
      cin >> m;
      v.push_back(m);
   }
}

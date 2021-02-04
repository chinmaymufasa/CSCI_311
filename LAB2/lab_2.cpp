//Tests 1
// CSCI 311 - Spring 2021
// Lab 2
// Author: Chinmay Satpanthi

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;


int triangleNum(int n){
  if (n == 1){
    return 1;
  }
  return triangleNum(n - 1) + n;
}

int rFib(int n){
  if (n == 0){
    return 0;

  }else if(n == 1){
    return 1;
  }
  return rFib(n - 1) + rFib(n - 2);
}

int rSum(const vector<int> &v){
  if (v.size() == 0){
    return 0;
  }
  return rSum(());
  return 0;
}

int helperFunction(int n){
    
}

int rMax(const vector<int> &v){
  return 0;
}

bool isSorted(const vector<int> &v, int start, int end){
  return false;
}

bool isPalindrome(string s){
  return false;
}

int rBinarySearch(const vector<int> &v, int low, int high, int target){
  return 0;
}

bool rSubsetSum(const vector<int> &v, int start, int target){
  return false;
}

/***********************************************
 * Main and helper functions for quick testing *
 * *********************************************/
void readIntVector(vector<int> &v, int n);

int main(){
  int question = -1;
  cin >> question;

  int n = 0, start = 0, end = 0;
  vector<int> v;
  string s = "";
  cin >> n;
  switch (question){
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
      cout << rBinarySearch(v, 0, v.size()-1, end) << endl;
      break;
    case 8: //rSubsetSum
      cin >> end;
      readIntVector(v, n);
      cout << rSubsetSum(v, 0, end) << endl;
      break;
  }

  return 0;
}

void readIntVector(vector<int> &v, int n){
  int m = 0;
  for (int i = 0; i < n; i++){
    cin >> m;
    v.push_back(m);
  }
}

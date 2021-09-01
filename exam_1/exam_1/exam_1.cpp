// CSCI 311 - Spring 2021
// Exam 1
// Author: ** Chinmay Satpanthi ***

#include <iostream>
#include <vector>
#include <string>
using namespace std;

/**************************
 * Your solutions go here *
 * ************************/

/*
This function compares two string and checks if the strings have a similar or
different character at the same index. +1 if different
*/
int hammingDist(string a, string b) {
   if (unsigned(a.length()) != unsigned(b.length())) {         //checks if both string lenghts match
      return  -1;
   }
   int hammingCount = 0;
   for (int i = 0; i < unsigned(a.length()); i++) {            
      if (a[i] != b[i]) {                                      //compares the char at the index
         hammingCount += 1;                                    //if different we add one to total counter
      }
   }
   return hammingCount;                                        //returns final answer
}


/*
This function reverses a provided string
*/
string reverse(string a) {
   int string_size = a.length();                               //stores string size
    
   if (string_size == 1) {                                     //checks if only size 1, if so returns the string
      return a;
   }
   for (int i = 1; i <= (string_size)/2; i++) {                //for half the string size we compare/switch characters 
      if (a[i - 1] != a[string_size - i]) {                    //if chars comparing are different we switch them
         char temp = a[i - 1];                                 //bubble sorting the characters
         a[i - 1] = a[string_size - i];
         a[string_size - i] = temp;
      }
   }
   return a;                                                   //returns the reversed string
}

/*
This function counts the number of consecutive similar characters and writes it in front of it
*/
string runLengthEncoding(string a) {
   int og_str_len = a.length();                                //keeps main string length
   string output = "";                                         //initialize main output string
   int char_counter = 1;                                       //total of each char counter
   char curr_char = a[0];                                      //initialize the variable with the first char

   if (og_str_len == 1) {                                      //checks for single char
      return "1" + a;
   }
   for (int i = 1; i <= og_str_len; i++) {
      if (curr_char == a[i]) {                                 //if consecutive char is similar then add one to counter
         char_counter += 1;
      }
      else {
         output += to_string(char_counter);                    //if consecutive char is different collect the counter and switch to string
         output += curr_char;                                  //add the string counter to the output string
         
         curr_char = a[i];                                     //now we look at the new char
         char_counter = 1;                                     //set counter back to 1
      }
   }
   return output;                                              //return output
}  


/*
This is a merge sort helper that helps compare the branches of the divided tree and send updated sorting index to the vector
*/
vector <int> mergeSortHelper(vector<int> left_side , vector<int> right_side) {
   vector<int> sorted;                                         //initialize sorting vector

   while (left_side.size() > 0 || right_side.size() > 0) {     //checks if either left or right side vectors are populated
      if (left_side.size() > 0 && right_side.size() > 0) {     //if we have both sides populated we check to see which is greater
         if (left_side[0] >= right_side[0]) {                  //checks if first value of left side is greater than right side
            sorted.push_back(right_side[0]);                   //if so we add it to the sort list
            right_side.erase(right_side.begin());              //we remove the first element from the left side
         }
         else {
            sorted.push_back(left_side[0]);                    //if right was smaller then we add that to the sort list
            left_side.erase(left_side.begin());                //we romve the element
         }
      }                                                        //if only one side is populated
      else if (right_side.size() > 0) {                        
         for (unsigned int i = 0; i < right_side.size(); i++)  
            sorted.push_back(right_side[i]);                   //we add the remaining of right to the sort list
         break;
      }
      else if (left_side.size() > 0) {
         for (unsigned int i = 0; i < left_side.size(); i++)
            sorted.push_back(left_side[i]);                    //or if only the left side is populated
         break;
      }
   }
   return sorted;                                              //we return the sorting we have done so far        
}


/*
This functions sorts a given integer populated vector from small to big and uses the merge sort helper function
to help traverse through each branch in the merge sort tree
*/
vector<int> mergeSort(const vector<int>& v) {
   vector<int> left_side, right_side, final;                   //initializes the two sides and the final vector

   if (v.size() <= 1)                                          //if solo size then we return vector
      return v;

   int mid_point = (v.size() + 1) / 2;                         //finds the mid point of the vector

   for (unsigned int i = mid_point; i < v.size(); i++) {       
      right_side.push_back(v[i]);                              //populates the right half of the vector
   }

   for (int i = 0; i < mid_point; i++) {
      left_side.push_back(v[i]);                               //populates the left half of the vector
   }
   return final = mergeSortHelper(mergeSort(left_side), mergeSort(right_side));   //recursively call the function till we have passed through all branches  
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
int main() {
   int question = -1;
   cin >> question;

   string a = "";
   string b = "";
   int n = -1;
   vector<int> v;
   vector<int> s;
   switch (question) {
   case 1: // Hamming distance
     /*************************************
      * Input format:                     *
      * 1                                 *
      * string 1, no whitespace, nonempty *
      * string 2, no whitespace, nonempty *
      * ***********************************/
      cin >> a >> b;
      cout << hammingDist(a, b) << endl;
      break;
   case 2: // reverse
     /**********************************************
      * Input format:                              *
      * 2                                          *
      * string to reverse, no whitespace, nonempty *
      * ********************************************/
      cin >> a;
      cout << reverse(a) << endl;
      break;
   case 3: // run-length encoding
     /*********************************************
      * Input format:                             *
      * 3                                         *
      * string to encode, no whitespace, nonempty *
      * *******************************************/
      cin >> a;
      cout << runLengthEncoding(a) << endl;
      break;
   case 4: // merge sort
     /*************************************
      * Input format:                     *
      * 4                                 *
      * length of vector                  *
      * integers to include in the vector *
      * ***********************************/
      cin >> n;
      readIntVector(v, n);
      s = mergeSort(v);
      for (int i = 0; i < s.size(); i++) { cout << s[i] << " "; }
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
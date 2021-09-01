// test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


using namespace std;


void call_this() {
   int arr_L [8] = {8,7,6,5,4,3,2,1};
   
   bool changed = true;
   int n = size(arr_L);
   while (changed) {
      changed = false;
      for (int i = 1; i < n - 1; i++) {
         if (arr_L[i - 1] > arr_L[i]) {
            int x = arr_L[i - 1];
            arr_L[i - 1] = arr_L[i];
            arr_L[i] = x;
            changed = true;
         }
         
      }
      n = n - 1;

   }


}


int main()
{
    call_this();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

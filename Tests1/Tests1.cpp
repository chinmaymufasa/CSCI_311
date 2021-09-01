// Tests1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <list>
#include <math.h>

using namespace std;

int newHash(string s);

int main()
{
   
   vector<vector<string>> table;
   
   while (1) {
      string s = "";
      cout << "Enter string: ";
      cin >> s;
      cout << endl;
      for (int i = 0; i < 11; i++) {
          
      }

      int power_value = 0;
      int hash_value = 0;
      unsigned int hash_index = 0;
      for (unsigned int i = 0; i < s.length(); i++) {
         hash_value += int(s[i]) * pow(2,power_value);
         power_value++;
      }
   
      hash_index = hash_value % 11;
      table.resize(11);
      table[hash_index].push_back(s);

      for (unsigned int i = 0; i < table.size(); i++) {
         if (table[i].size() > 0) {
            cout << i << ": ";
            for (unsigned int j = 0; j < table[i].size() - 1; j++) {
               cout << table[i][j] << ", ";
            }
            cout << table[i][table[i].size() - 1] << endl;
         }
      }
   
      vector<string> temp;

      for (unsigned int i = 0; i < table.size(); i++) {
         if (table[i].size() > 0) {
            for (int j = 0; j < table[i].size(); j++) {
               temp.push_back(table[i][j]);
            }
         }
      }

      table.clear();
      table.resize(59);
      for (int i = 0; i < temp.size(); i++) {
         unsigned int index = newHash(temp[i]);
         table[index].push_back(temp[i]);
      }
      //table.resize(59);

   }
}

int newHash(string s) {
   int power_value = 0;
   unsigned int hash_value = 0;
   for (int i = 0; i < s.length(); i++) {
      hash_value += int(s[i]) * pow(2, power_value);
      power_value++;
   }
   return hash_value % 59;
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

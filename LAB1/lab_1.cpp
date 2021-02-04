// CSCI 311 - Spring 2021
// Lab 1
// Author: Chinmay Satpanthi // Lab Help

#include <iostream>
#include <math.h>
#include <chrono>
#include <vector>

using namespace std;

/*
This funtion uses the provided n from user to determine how many loops it takes to get to 1
by either halving the n or multiplying it by three and adding one then going again.
*/
int collatzLength(int n){
    int total = 0;          //initializing total variable
    if (n < 0){             //checking for a negative n value
        return 0;           
    }
    while (n > 1){          //checking if n has reached one yet
        if (n%2==0){        //test if n is an even number 
            n /= 2;         //then set n equal to half its own value
        }else
        {
            n = n*3 + 1;    //if n was odd number then multiply by 3 and add 1 to it
        }
        total++;            //increment the total count
    }

    return total;           //once we loop out we can return the collatzLength of n
}


/*
This funtion has store n data from user and determines the MIN, MEAN and MAX of the set of
data and displays the output.
*/
void printStats(const vector<int> &v){

  int min = v.at(0);                        //sets min to first value from vector
  double mean = v.at(0);                    //sets mean to first value from vector
  int max = v.at(0);                        //sets max to first value from vector  
  double total = v.at(0);                      //sets total to first value from vector


  if (v.size() == 1){                       //checks if vector size is one therefore all three values will be the same
    cout << "min: " << min << endl;         //prints out the min
    cout << "mean: " << mean << endl;       //prints out the mean
    cout << "max: " << max << endl;         //prints out the max
  }
  else{
    for(int i = 1; i < v.size(); i++){      //loops through the vector starting at v.at(1) since we already assigned 0 at the start
      if(v.at(i) < min){                    //checks if the value is less than min
        min = v.at(i);                      //if so, assigns min the new value
      }
      else if(v.at(i) > max){               //else it checks if is greater than the max value
        max = v.at(i);                      //if so, assigns max the new value
      }
      total += v.at(i);                     //end of each iteration adds the vector number to total 
    }
    int size = v.size();
    mean = total / size;                //finds the mean of the vector set

    cout << "min : " << min << endl;        //prints out the min
    printf("mean %.2f\n", mean);     //prints out the mean
    cout << "max : " << max << endl;        //prints out the max
  }
}

/*
This function returns the sum of all multiples of values in the vector nums less than n.
The functions also makes sure common multiple duplicates are not added to the total sum
*/
int sumMultiples(const vector<int> &nums, int n){
    int total = 0;                                                     //initialize variable total                       

    for (int i = 0; i < nums.size(); i++){                             //This loops through all the values in the vector
      
      int nums_multiples = 0;                                          //initialize variable num_multiples 

      if(n%nums.at(i) == 0){                                           //checks to see if the value in the vector is a multiple of n
        nums_multiples = (n/nums.at(i)) - 1;                           //if so we will avoid the last multiple since we are looking for sums less than n
      }
      else{
        nums_multiples = n/nums.at(i);                                 //if not a multuple then we keep the number of multiples at the same value
      } 
      
      int natural_sum = nums_multiples * (nums_multiples + 1) / 2;     //this finds the total of the number 1 to total number of multiples
      int multiples_tot = nums.at(i) * natural_sum;                    //we now multiply the previous sum by the number from the vector

      total += multiples_tot;                                          //we add the value to the total

      for(int j = i+1; j < nums.size(); j++){                          /*this is a second for loop to iterate through the vector to find all common 
                                                                       multiples that we will remove from the total*/
        int common_multiples = nums.at(i) * nums.at(j);                //this multiples both the vector values to find the common multiple

        int num_common_multiples = 0;                                  //initializes value num_common_multiples for the duplicates
        int tot_common_multiples = 0;                                  //initializes value tot_common_multiples for the total value of multiples

        if (n%common_multiples == 0){                                  //checks if the common multiple id a multiple of n
           num_common_multiples = (n / common_multiples) - 1;          //if so we will avoid the last multiple
        }
        else{
           num_common_multiples = n / common_multiples;                //this finds the total number of duplicate common values
        }
        tot_common_multiples = num_common_multiples * (num_common_multiples + 1) / 2;   //finds the natural total from 1 to number of duplicates values
        tot_common_multiples *= common_multiples;                      //we multiply the previous value with duplicate value and add it to the total duplicate value
        total -= tot_common_multiples;                                 //here we remove the total duplicate value we got so far from the grand total
      }
    }   
    return total;                                                      //returns the final total 
}

/*
This function reads a vector and retunrs the vector with only values greater than k
*/
void greaterThanK(vector<int> &v, int k){

  vector<int> temp(v);                          //sets all the values in new vector (temp) as the values in v 
  v.clear();                                    //clear out all the elements from v

  for (int i = 0; i < temp.size(); i++){        //this loop iterates through all elements in temp vector
    
    if (temp.at(i) > k){                        //if the value in temp is greater than k
      v.push_back(temp.at(i));                  //we add the element to the v vector
    }
  }
}

/*
This function rearranges the elements in the vector provided by moving all the values less than k appear before 
the values greater than k
*/
void pivot(vector<int> &v, int k){

  int j = v.size() - 1;                       //initializes variable j as the size of the vector
  int i = 0;                                  //initializes variable i as zero 

  while(i < j){                               //checks if values i and j have not crossed yet
    if(v.at(i) > k && v.at(j) <= k){          //checks if the value at i is greater than k and if value at j is less than k
      swap(v[i],v[j]);                        //if this holds true then we swap the values 
      i++;                                    //increments i
      j--;                                    //decrements j
    }
    else if(v.at(i) > k && v.at(j) > k){      //checks if value at i is greater than k and value at j is greater
      j--;                                    //if so decrements j because we a looking for another value to swap
    }
    else{
      i++;                                    //if no statements check then we simply increment i
    }
  }
}

/* 
This function checks if vector a is a sequential subarray of b, returns true if subarray

*/
bool isSubarray(const vector<string> &a, const vector<string> &b){

  if(a.size() == b.size() && a == b){                           //checks if size is same to to minimize steps
    return true;                                                //is both the vectors are the same 
  }
  else if (a.size() == b.size() && a != b){                     //if the size of vectors are the same and not equal then they are not subarrays
    return false;                                               //returns false 
  }else{

  int negate_size = a.size() - 1;                               //leaves of last size of main array since if the first doesnt count

  for (int i = 0; i < b.size() - negate_size; i++){             //checks all the values excluding the last few in main array
    if (b.at(i) == a.at(0)){                                    //if the selected element match then we check to see if the others match
      if (a.size() == 1){                                       //if the subarray is only size one then a true means it is a subarray
        return true;
      }
      else{
        for (int j = 0; j < a.size(); j++){                     //iterates through the subarray
          if (b.at(i + j) == a.at(j) && j == a.size() - 1){     //if both the last elements match then retunrn true
            return true;    
          }
          else if (b.at(i + j) != a.at(j)){                     //if elements are different then break loop
            break;
          }      
        }    
      }     
    }
  
  }
  return false;                                                 //since no match was found we return false
  }
}

/* 
This function checks the provided int n is a prime by checking all the mods between
2 and the int n
 */

bool isPrimeA(int n){

  for (int i = 2; i <= n/2; i++){     //for all elements between 2 and n loop
    if (n % i == 0){                  //if there is a multiple for the number other than itself and two returns false for non prime number
      return false;
    }
  } 
  return true;                        //if we reach end of loop then n is a prime number
}

/* 
This function adds the prime numbers for all odd numbers to n and checks if i is 
prime by calling isPrimeA function.

 */
int sumPrimesA(int n){

  int prime_total = 0;                //initializes the prime total variable
  for (int i = 2; i < n; i++){        //for all numbers till n 
    if (i % 2 != 0 || i == 2){        //checks only odd numbers other than 2 to limit calls
      if (isPrimeA(i)){               //calls isPrimeA to check if is prime
        prime_total += i;             //if true adds to prime
      }        
    }

  }
    return prime_total;               //returns final total of all prime number to n
}


/* 
This function is an optimized version of the previous prime number checks by reducing the count to 
square root of n
 */
bool isPrimeB(int n){
  for (int i = 2; i <= sqrt(n); i++){ //for all elements between 2 and square root of n loop
    if (n % i == 0){                  //if there is a multiple for the number other than itself and two returns false for non prime number
      return false;
    }
  } 
  return true;                        //if we reach end of loop then n is a prime number
}


int sumPrimesB(int n){
  int prime_total = 0;                //initializes the prime total variable
  for (int i = 2; i < n; i++){        //for all numbers till n 
    if (i % 2 != 0 || i == 2){        //checks only odd numbers other than 2 to limit calls
      if (isPrimeB(i)){               //calls isPrimeA to check if is prime
        prime_total += i;             //if true adds to prime
      }        
    }
  }
  return prime_total;               //returns final total of all prime number to n
}


/* 
This funtion is an effiecient version of prime addition by using specific limits and eliminating 
extra cycles 

 */
int sieveOfErathosthenes(int n){
  vector<int> v;                                //initialize vairable
  
  for(int i = 2; i < n; i++){                   //populate with the numbers to n
    v.push_back(i);    
  }

  for(int i = 2; i < sqrt(n); ++i){             //for all value till squareroot of n, loop
    if(v.at(i)){                                //if not marked yet
      for(int j = i*i; j < v.size(); j += i){   //loop the multiple of i so we can mark them
        v.at(j) = 0;                            //mark the indexs with 0 
      }
    }
  }

  vector<int>prime;                             //initialize new variable
  for (int i = 2; i < v.size(); ++i){           //sending the good values from previous vector to new
    if( v.at(i)){                           
    prime.push_back(i);                         //push to new vector
    }
  }

  long total = 0;                               //initializes total variable
  for(int i = 0; i < prime.size(); ++i){        //loop through new vector 
    total += prime.at(i);                       //add up all the prime numbers
  }
  return total;                                 //return the total
}




/***********************************************
 * Main and helper functions for quick testing *
 * *********************************************/
void readIntVector(vector<int> &v, int n);
void timePrimes();

int main(){
  int question = -1;
  cin >> question;

  int n = 0, k = 0, m = 0;
  vector<int> v;
  string s = "";
  vector<string> a;
  vector<string> b;

  switch (question){
    case 1: //collatzLength
      cin >> n;
      cout << collatzLength(n) << endl;
      break;
    case 2: //printStats
      cin >> n;
      readIntVector(v, n);
      printStats(v);
      break;
    case 3: //sumMultiples
      cin >> n;
      readIntVector(v, n);
      cin >> k;
      cout << sumMultiples(v, k) << endl;
      break;
    case 4: //greaterThanK
      cin >> n;
      readIntVector(v, n);
      cin >> k;
      greaterThanK(v, k);
      for (int j = 0; j < v.size(); j++){ cout << v[j] << " "; }
      break;
    case 5: //pivot
      cin >> n;
      readIntVector(v, n);
      cin >> k;
      pivot(v, k);
      for (int j = 0; j < v.size(); j++){ cout << v[j] << " "; }
      break;
    case 6: //isSubarray
      cin >> n >> m;
      for (int i = 0; i < n; i++){
        cin >> s;
        a.push_back(s);
      }
      for (int i = 0; i < m; i++){
        cin >> s;
        b.push_back(s);
      }
      cout << isSubarray(a, b) << endl;
      break;
    case 7: //primes
      cin >> n;
      cout << sumPrimesA(n) << " " << sumPrimesB(n) << " " << sieveOfErathosthenes(n) << endl;
      break;
    case 8: //time primes
      timePrimes();
      break;
  }

  return 0;
}

/**************************************************
 * Read a vector of integers in from cin          *
 * v - vector<int> & - the integer vector to fill *
 * n - int - the number of integers to read       *
 * ************************************************/
void readIntVector(vector<int> &v, int n){
  int m = 0;
  for (int i = 0; i < n; i++){
    cin >> m;
    v.push_back(m);
  }
}

/***************************************************************************************************
 * Testing run times of different approaches to finding the sum of prime numbers under a threshold *
 * *************************************************************************************************/
void timePrimes(){
  int sum = -1;
  chrono::high_resolution_clock::time_point start;
  chrono::high_resolution_clock::time_point end;
  double elapsed = -1;
  vector<int> x = {10, 100, 1000, 10000, 100000, 500000};
  for (int i = 0; i < x.size(); i++)
  {
    cout << "Value: " << x[i] << endl;

    start = chrono::high_resolution_clock::now();
    sum = sumPrimesA(x[i]);
    end = chrono::high_resolution_clock::now();
    elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
    cout << "A ... Sum: " << sum << ", Time elapsed: " << elapsed << endl;

    start = chrono::high_resolution_clock::now();
    sum = sumPrimesB(x[i]);
    end = chrono::high_resolution_clock::now();
    elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
    cout << "B ... Sum: " << sum << ", Time elapsed: " << elapsed << endl;

    start = chrono::high_resolution_clock::now();
    sum = sieveOfErathosthenes(x[i]);
    end = chrono::high_resolution_clock::now();
    elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
    cout << "C ... Sum: " << sum << ", Time elapsed: " << elapsed << endl;
    cout << endl << endl;
  }

  cout << "Sieve of Erathosthenes on primes below 1 million" << endl;
  start = chrono::high_resolution_clock::now();
  long sum2 = sieveOfErathosthenes(1000000);
  end = chrono::high_resolution_clock::now();
  elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
  cout << "Sum: " << sum2 << ", Time elapsed: " << elapsed << endl;
  cout << endl << endl;
}

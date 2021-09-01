/*
Chinmay Satpanthi
CSCI 311
Project 1
*/



#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <math.h>
#include <chrono>
#include <fstream>

using namespace std;

//class to store data from calculations
class Data {
public:
			vector<double> bub_time, ins_time, sel_time, qui_time;
			double bub_min = 0, bub_max = 0, bub_SD = 0, bub_mean = 0;
			double ins_min = 0, ins_max = 0, ins_SD = 0, ins_mean = 0;
			double sel_min = 0, sel_max = 0, sel_SD = 0, sel_mean = 0;
			double qui_min = 0, qui_max = 0, qui_SD = 0, qui_mean = 0;
			
};

//global Object variables
Data testrun;
Data Worsecase;
Data Averagecase;
Data Bestcase;

//returns a random vecotr given size and range
vector<int> randomVector(int size, int low, int high) {
			vector<int> v(size, 0);
			for (int i = 0; i < size; i++) {
						v[i] = rand() % (high - low + 1) + low;
			}
			return v;
}

//prints vector (test purposes)
void printVector(const vector<int>& v, string typesort) {
			cout << typesort << endl;
			for (unsigned int i = 0; i < v.size(); i++) {
						cout << v[i] << " ";
			}
			cout << endl;
}

//checks is vector is sorted
bool isSorted(const vector<int>& v) {
			unsigned int i = 0;
			while (i < v.size() - 1) {
						if (v[i] > v[i + 1]) {
									return false;
						}
						i++;
			}
			return true;
}

//bubble sort algorithm sorts data increasing order
void bubbleSort(vector<int>& v) {
			bool check_swap;
			for (unsigned int i = 0; i < v.size() - 1; i++) {
						check_swap = false;
						for (unsigned int j = 0; j < v.size() - i - 1; j++) {
									if (v[j] > v[j + 1]) {
												int temp = v[j];
												v[j] = v[j+ 1];
												v[j + 1] = temp;
												check_swap = true;
									}
						}
						if (check_swap == false) {
									break;
						}
			}
}

//insertion sort algorith, sorts data increasing order
void insertionSort(vector<int>& v) {
			for (unsigned int i = 1; i < v.size(); i++)
			{
						int key = v[i];
						int j = i - 1;
						while (j >= 0 && v[j] > key)
						{
									v[j + 1] = v[j];
									j--;
						}
						v[j + 1] = key;
			}
}

//selection sort algorithm, sorts data increasing order
void selectionSort(vector<int>& v) {
			for (unsigned int i = 0; i < v.size() - 1; i++) {
						int min = i;
						for (unsigned int j = i + 1; j < v.size(); j++) {
									if (v[min] > v[j]) {
												min = j;
									}
						}
						if (min != i) {
									int temp = v[min];
									v[min] = v[i];
									v[i] = temp;
						}
			}
}

//quicksort helper function 
int quickSortHelper(vector<int>& v, int low, int high) {
			int l = (low - 1);
			int h = v[high];

			for (int i = low; i <= high - 1; i++) {
						if (v[i] <= h) {
									l += 1;
									int temp = v[l];
									v[l] = v[i];
									v[i] = temp;
						}
			}
			int temp = v[l + 1];
			v[l + 1] = v[high];
			v[high] = temp;
			return l + 1;
}

//quicksort function, sorts dat increasing order
void quickSort(vector<int>& v, int low, int high) {
			if (low < high) {
						int pivot = quickSortHelper(v, low, high);
						quickSort(v, low, pivot - 1);
						quickSort(v, pivot + 1, high);
			}
}

//this function calculatese the mean of the vector provided
double dataMean(const vector<double> v) {
			double mean = 0;
			for (unsigned int i = 0; i < v.size(); i++) {
						mean += v[i];
			}
			mean = mean / v.size();
			return mean;
}

//finds the max value in the vector
double dataMax(const vector<double>& v) {
			double max = v[0];
			for (unsigned int i = 1; i < v.size(); i++) {
						if (v[i] > max) {
									max = v[i];
						}
			}
			return max;
}

//finds the min value in the vector
double dataMin(const vector<double>& v) {
			double min = v[0];
			for (unsigned int i = 1; i < v.size(); i++) {
						if (v[i] < min) {
									min = v[i];
						}
			}
			return min;
}

//finds the standard deviation of vector
double dataSD(const vector<double> v) {
			double mean = dataMean(v);
			double sd = 0;
			for (unsigned int i = 0; i < v.size(); i++) {
						sd += (v[i] - mean) * (v[i] - mean);
			}
			sd = sd / (v.size() - 1);
			return sqrt(sd);
}

//calculates the Min,Max,SD,Mean of all four sorting algorithms
void calculateData() {

			testrun.bub_SD = dataSD(testrun.bub_time);
			testrun.bub_mean = dataMean(testrun.bub_time);
			testrun.bub_min = dataMin(testrun.bub_time);
			testrun.bub_max = dataMax(testrun.bub_time);

			testrun.ins_SD = dataSD(testrun.ins_time);
			testrun.ins_mean = dataMean(testrun.ins_time);
			testrun.ins_min = dataMin(testrun.ins_time);
			testrun.ins_max = dataMax(testrun.ins_time);

			testrun.sel_SD = dataSD(testrun.sel_time);
			testrun.sel_mean = dataMean(testrun.sel_time);
			testrun.sel_min = dataMin(testrun.sel_time);
			testrun.sel_max = dataMax(testrun.sel_time);

			testrun.qui_SD = dataSD(testrun.qui_time);
			testrun.qui_mean = dataMean(testrun.qui_time);
			testrun.qui_min = dataMin(testrun.qui_time);
			testrun.qui_max = dataMax(testrun.qui_time);
}

//prints out the rigourous calculations data
void printRigData(int vects) {
			cout << "Vector size: " << vects << endl;
			cout << "*******************************************" << endl;
			cout << "Bubble sort: " << endl;
			cout << "Worse case mean: " << Worsecase.bub_mean << endl;
			cout << "Worse case SD:   " << Worsecase.bub_SD << endl;
			cout << "Average case mean:  " << Averagecase.bub_mean << endl;
			cout << "Average case SD:" << Averagecase.bub_SD << endl;
			cout << "Best case mean:"  << Bestcase.bub_mean << endl;
			cout << "Best case SD:" << Bestcase.bub_SD << endl;
			cout << "*******************************************" << endl;
			cout << endl;
			cout << "*******************************************" << endl;
			cout << "Insertion sort: " << endl;
			cout << "Worse case mean: " << Worsecase.ins_mean << endl;
			cout << "Worse case SD:   " << Worsecase.ins_SD << endl;
			cout << "Average case mean:  " << Averagecase.ins_mean << endl;
			cout << "Average case SD:" << Averagecase.ins_SD << endl;
			cout << "Best case mean:" << Bestcase.ins_mean << endl;
			cout << "Best case SD:" << Bestcase.ins_SD << endl;
			cout << "*******************************************" << endl;
			cout << endl;
			cout << "*******************************************" << endl;

			cout << "Selection sort: " << endl;
			cout << "Worse case mean: " << Worsecase.sel_mean << endl;
			cout << "Worse case SD:   " << Worsecase.sel_SD << endl;
			cout << "Average case mean:  " << Averagecase.sel_mean << endl;
			cout << "Average case SD:" << Averagecase.sel_SD << endl;
			cout << "Best case mean:" << Bestcase.sel_mean << endl;
			cout << "Best case SD:" << Bestcase.sel_SD << endl;
			cout << "*******************************************" << endl;
			cout << endl;
			cout << "*******************************************" << endl;
			cout << "Quicksort sort: " << endl;
			cout << "Worse case mean: " << Worsecase.qui_mean << endl;
			cout << "Worse case SD:   " << Worsecase.qui_SD << endl;
			cout << "Average case mean:  " << Averagecase.qui_mean << endl;
			cout << "Average case SD:" << Averagecase.qui_SD << endl;
			cout << "Best case mean:" << Bestcase.qui_mean << endl;
			cout << "Best case SD:" << Bestcase.qui_SD << endl;
			cout << "*******************************************" << endl;
			cout << endl;
			cout << endl;
}


//This functions calculates the larger data recorded for each algorithm
void calculateRigData() {
			int n,m;

			//here we partition the vectors into 50 for calculation purposes
			for (int i = 0; i < 5; i++) {
						if (i == 0) {
									n = 0;
									m = 49;
						}
						else if (i == 1) {
									n = 50;
									m = 99;
						}
						else if (i == 2) {
									n = 100;
									m = 149;
						}
						else if (i == 3) {
									n = 150;
									m = 199;
						}
						else if (i == 4) {
									n = 200;
									m = 249;
						}

						//we simply do the calculations of the 50 vectos here and store them
						vector<double> temp (Worsecase.bub_time.begin() + n, Worsecase.bub_time.begin()+ m);
						Worsecase.bub_SD = dataSD(temp);
						Worsecase.bub_mean = dataMean(temp);

						vector<double> temp1(Averagecase.bub_time.begin() + n, Averagecase.bub_time.begin() + m);
						Averagecase.bub_SD = dataSD(temp1);
						Averagecase.bub_mean = dataMean(temp1);

						vector<double> temp2(Bestcase.bub_time.begin() + n, Bestcase.bub_time.begin() + m);
						Bestcase.bub_SD = dataSD(temp2);
						Bestcase.bub_mean = dataMean(temp2);

						vector<double> temp3(Worsecase.ins_time.begin() + n, Worsecase.ins_time.begin() + m);
						Worsecase.ins_SD = dataSD(temp3);
						Worsecase.ins_mean = dataMean(temp3);

						vector<double> temp4(Averagecase.ins_time.begin() + n, Averagecase.ins_time.begin() + m);
						Averagecase.ins_SD = dataSD(temp4);
						Averagecase.ins_mean = dataMean(temp4);

						vector<double> temp5(Bestcase.ins_time.begin() + n, Bestcase.ins_time.begin() + m);
						Bestcase.ins_SD = dataSD(temp5);
						Bestcase.ins_mean = dataMean(temp5);

						vector<double> temp6(Worsecase.sel_time.begin() + n, Worsecase.sel_time.begin() + m);
						Worsecase.sel_SD = dataSD(temp6);
						Worsecase.sel_mean = dataMean(temp6);

						vector<double> temp7(Averagecase.sel_time.begin() + n, Averagecase.sel_time.begin() + m);
						Averagecase.sel_SD = dataSD(temp7);
						Averagecase.sel_mean = dataMean(temp7);

						vector<double> temp8(Bestcase.sel_time.begin() + n, Bestcase.sel_time.begin() + m);
						Bestcase.sel_SD = dataSD(temp8);
						Bestcase.sel_mean = dataMean(temp8);

						vector<double> temp9(Worsecase.qui_time.begin() + n, Worsecase.qui_time.begin() + m);
						Worsecase.qui_SD = dataSD(temp9);
						Worsecase.qui_mean = dataMean(temp9);

						vector<double> temp10(Averagecase.qui_time.begin() + n, Averagecase.qui_time.begin() + m);
						Averagecase.qui_SD = dataSD(temp10);
						Averagecase.qui_mean = dataMean(temp10);

						vector<double> temp11(Bestcase.qui_time.begin() + n, Bestcase.qui_time.begin() + m);
						Bestcase.qui_SD = dataSD(temp11);
						Bestcase.qui_mean = dataMean(temp11);
			
						double vects = exp2(i+2) * 50;
						printRigData(vects);
			}

}

//simple error print function
void errorPrint(string s) {
			cout << "Sorting error with " << s << endl;
}

//checks the time taken for sorting the average case for each algorithm
void rigorousAvgCheck(int size) {

			chrono::high_resolution_clock::time_point start;
			chrono::high_resolution_clock::time_point end;
			vector<int> v_duplicate;
			double elapsed = 0;


			//we calcualate the average time fror each alorithm
			for (int i = 0; i < 50; i++) {
						const vector<int> v = randomVector(size, 1, size);
						v_duplicate = v;
						start = chrono::high_resolution_clock::now();
						bubbleSort(v_duplicate);
						end = chrono::high_resolution_clock::now();
						elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
						if (!isSorted(v_duplicate)) {
									errorPrint("Bubble Sort");
						}
						Averagecase.bub_time.push_back(elapsed);

						//avg for insertion
						v_duplicate = v;
						start = chrono::high_resolution_clock::now();
						insertionSort(v_duplicate);
						end = chrono::high_resolution_clock::now();
						elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
						if (!isSorted(v_duplicate)) {
									errorPrint("Insertion Sort");
						}
						Averagecase.ins_time.push_back(elapsed);

						//avg for selection
						v_duplicate = v;
						start = chrono::high_resolution_clock::now();
						selectionSort(v_duplicate);
						end = chrono::high_resolution_clock::now();
						elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
						if (!isSorted(v_duplicate)) {
									errorPrint("Selection Sort");
						}
						Averagecase.sel_time.push_back(elapsed);

						//avg for quick
						v_duplicate = v;
						start = chrono::high_resolution_clock::now();
						quickSort(v_duplicate, 0, v_duplicate.size() - 1);
						end = chrono::high_resolution_clock::now();
						elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
						if (!isSorted(v_duplicate)) {
									errorPrint("Quick Sort");
						}
						Averagecase.qui_time.push_back(elapsed);
						Bestcase.qui_time.push_back(elapsed);
			}
}

//records the best and worst case of the algorithms
void rigorousCheck(const vector<int> &v, char test_case) {

			chrono::high_resolution_clock::time_point start;
			chrono::high_resolution_clock::time_point end;
			vector<int> v_duplicate;
			double elapsed = 0;		

						
			for (int i = 0; i < 50; i++) {
						v_duplicate = v;
						start = chrono::high_resolution_clock::now();
						bubbleSort(v_duplicate);
						end = chrono::high_resolution_clock::now();
						elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
						if (!isSorted(v_duplicate)) {
									errorPrint("Bubble Sort");
						}
						switch (test_case) {
									case 'w':
												Worsecase.bub_time.push_back(elapsed);
												break;
									case 'b':
												Bestcase.bub_time.push_back(elapsed);
												break;
									default :
												break;
						}

						//finds the best and worst for insertions
						v_duplicate = v;
						start = chrono::high_resolution_clock::now();
						insertionSort(v_duplicate);
						end = chrono::high_resolution_clock::now();
						elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
						if (!isSorted(v_duplicate)) {
									errorPrint("Insertion Sort");
						}
						switch (test_case) {
						case 'w':
									Worsecase.ins_time.push_back(elapsed);
									break;
						case 'b':
									Bestcase.ins_time.push_back(elapsed);
									break;
						default:
									break;
						}

						//finds the best and worst for selecton
						v_duplicate = v;
						start = chrono::high_resolution_clock::now();
						selectionSort(v_duplicate);
						end = chrono::high_resolution_clock::now();
						elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
						if (!isSorted(v_duplicate)) {
									errorPrint("Selection Sort");
						}
						switch (test_case) {
						case 'w':
									Worsecase.sel_time.push_back(elapsed);
									break;
						case 'b':
									Bestcase.sel_time.push_back(elapsed);
									break;
						default:
									break;
						}

						//finds the best and worst for quicksort
						v_duplicate = v;
						start = chrono::high_resolution_clock::now();
						quickSort(v_duplicate, 0, v_duplicate.size() - 1);
						end = chrono::high_resolution_clock::now();
						elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
						if (!isSorted(v_duplicate)) {
									errorPrint("Quick Sort");
						}
						switch (test_case) {
						case 'b':
									Worsecase.qui_time.push_back(elapsed);
									break;
						default:
									break;
						}
			}
}

//This functions calculates the sample data for 10 vectors for runtime of each algorithms
bool testRunAlgorithms() {

			chrono::high_resolution_clock::time_point start;
			chrono::high_resolution_clock::time_point end;
			vector<int> v_duplicate;
			double elapsed = 0;
			for (int i = 0; i < 10; i++){
						const vector<int> v = randomVector(100, 1, 100);
						v_duplicate = v;
						start = chrono::high_resolution_clock::now();
						bubbleSort(v_duplicate);
						end = chrono::high_resolution_clock::now();
						elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
						if (!isSorted(v_duplicate)) {
									errorPrint("Bubble Sort");
									return false;
						}
						testrun.bub_time.push_back(elapsed);

						//avg time for sample insertion
						v_duplicate = v;
						start = chrono::high_resolution_clock::now();
						insertionSort(v_duplicate);
						end = chrono::high_resolution_clock::now();
						elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
						if (!isSorted(v_duplicate)) {
									errorPrint("Insertion Sort");
									return false;
						}
						testrun.ins_time.push_back(elapsed);

						//avg for sample slection sort
						v_duplicate = v;
						start = chrono::high_resolution_clock::now();
						selectionSort(v_duplicate);
						end = chrono::high_resolution_clock::now();
						elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
						if (!isSorted(v_duplicate)) {
									errorPrint("Selection Sort");
									return false;
						}
						testrun.sel_time.push_back(elapsed);

						//avg for sample quicksort
						v_duplicate = v;
						start = chrono::high_resolution_clock::now();
						quickSort(v_duplicate, 0, v_duplicate.size() - 1);
						end = chrono::high_resolution_clock::now();
						elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
						if (!isSorted(v_duplicate)) {
									errorPrint("Quick Sort");
									return false;
						}
						testrun.qui_time.push_back(elapsed);
			}
			return true;
}

//this function calls the necessary functions and feed the vectors that need to be calculated for runtime
void rigorousTesting() {
			vector<int> v_inc_200, v_inc_400, v_inc_800, v_inc_1600, v_inc_3200;
			vector<int> v_dec_200, v_dec_400, v_dec_800, v_dec_1600, v_dec_3200;
			vector<int> v_avg_200, v_avg_400, v_avg_800, v_avg_1600, v_avg_3200;

			//setting default sorted vectors for both increasing and decreasing
			for (int i = 1; i <= 3200; i++) {
						if (i <= 200) {
									v_inc_200.push_back(i);
									v_inc_400.push_back(i);
									v_inc_800.push_back(i);
									v_inc_1600.push_back(i);
									v_inc_3200.push_back(i);
									v_avg_200.push_back(1);
									v_avg_400.push_back(1);
									v_avg_800.push_back(1);
									v_avg_1600.push_back(1);
									v_avg_3200.push_back(1);
						}
						else if (i > 200 && i <= 400) {
									v_inc_400.push_back(i);
									v_inc_800.push_back(i);
									v_inc_1600.push_back(i);
									v_inc_3200.push_back(i);
									v_avg_400.push_back(1);
									v_avg_800.push_back(1);
									v_avg_1600.push_back(1);
									v_avg_3200.push_back(1);
						}
						else if (i > 400 && i <= 800) {
									v_inc_800.push_back(i);
									v_inc_1600.push_back(i);
									v_inc_3200.push_back(i);
									v_avg_800.push_back(1);
									v_avg_1600.push_back(1);
									v_avg_3200.push_back(1);
						}
						else if (i > 800 && i <=1600) {
									v_inc_1600.push_back(i);
									v_inc_3200.push_back(i);
									v_avg_1600.push_back(1);
									v_avg_3200.push_back(1);
						}
						else if (i > 1600 && i <= 3200) {
									v_inc_3200.push_back(i);
									v_avg_3200.push_back(1);
						}						
			}

			for (int i = 3200; i >= 1; i--) {
						if (i > 1600 && i <= 3200) {
									v_dec_3200.push_back(i);
						}
						else if (i > 800 && i <= 1600) {
									v_dec_1600.push_back(i);
									v_dec_3200.push_back(i);
						}
						else if (i > 400 && i <= 800) {
									v_dec_800.push_back(i);
									v_dec_1600.push_back(i);
									v_dec_3200.push_back(i);
						}
						else if (i > 200 && i <= 400) {
									v_dec_400.push_back(i);
									v_dec_800.push_back(i);
									v_dec_1600.push_back(i);
									v_dec_3200.push_back(i);
						}
						else if (i <= 200) {
									v_dec_200.push_back(i);
									v_dec_400.push_back(i);
									v_dec_800.push_back(i);
									v_dec_1600.push_back(i);
									v_dec_3200.push_back(i);
						}
			}

			//call the fucntions to send the vectors to given parameters to differentiate
			rigorousCheck(v_inc_200, 'b');
			rigorousCheck(v_inc_400, 'b');
			rigorousCheck(v_inc_800, 'b');
			rigorousCheck(v_inc_1600,'b');
			rigorousCheck(v_inc_3200,'b');
			rigorousCheck(v_dec_200, 'w');
			rigorousCheck(v_dec_400, 'w');
			rigorousCheck(v_dec_800, 'w');
			rigorousCheck(v_dec_1600,'w');
			rigorousCheck(v_dec_3200,'w');			
			rigorousAvgCheck(200);
			rigorousAvgCheck(400);
			rigorousAvgCheck(800);
			rigorousAvgCheck(1600);
			rigorousAvgCheck(3200);		
}

//sample case test run data print out
void printTestRuns() {
			cout << "*******************************************" << endl;
			cout << "Bubble sort on 10 vectors of length 100" << endl;
			cout << "Sorting successful" << endl;
			cout << "Minimum: " << testrun.bub_min << " sec" << endl;
			cout << "Mean:    " << testrun.bub_mean << " sec" << endl;
			cout << "SD:      " << testrun.bub_SD << " sec" << endl;
			cout << "Maximum: " << testrun.bub_max << " sec" << endl;
			cout << "*******************************************" << endl;
			cout << endl << endl;

			cout << "*******************************************" << endl;
			cout << "Isertion sort on 10 vectors of length 100" << endl;
			cout << "Sorting successful" << endl;
			cout << "Minimum: " << testrun.ins_min << " sec" << endl;
			cout << "Mean:    " << testrun.ins_mean << " sec" << endl;
			cout << "SD:      " << testrun.ins_SD << " sec" << endl;
			cout << "Maximum: " << testrun.ins_max << " sec" << endl;
			cout << "*******************************************" << endl;
			cout << endl << endl;

			cout << "*******************************************" << endl;
			cout << "Selection sort on 10 vectors of length 100" << endl;
			cout << "Sorting successful" << endl;
			cout << "Minimum: " << testrun.sel_min << " sec" << endl;
			cout << "Mean:    " << testrun.sel_mean << " sec" << endl;
			cout << "SD:      " << testrun.sel_SD << " sec" << endl;
			cout << "Maximum: " << testrun.sel_max << " sec" << endl;
			cout << "*******************************************" << endl;
			cout << endl << endl;

			cout << "*******************************************" << endl;
			cout << "Quick sort on 10 vectors of length 100" << endl;
			cout << "Sorting successful" << endl;
			cout << "Minimum: " << testrun.qui_min << " sec" << endl;
			cout << "Mean:    " << testrun.qui_mean << " sec" << endl;
			cout << "SD:      " << testrun.qui_SD << " sec" << endl;
			cout << "Maximum: " << testrun.qui_max << " sec" << endl;
			cout << "*******************************************" << endl;
			cout << endl << endl;

}

//main functions calls the major functions
int main() {

			srand(unsigned(time(NULL)));
			if (testRunAlgorithms()){
						calculateData();
						printTestRuns();
						cout << endl;
						cout << "Sample testing success!" << endl << endl;
						cout << "Running larger data... (might take a while)" << endl;
						rigorousTesting();
						calculateRigData();
			}

}
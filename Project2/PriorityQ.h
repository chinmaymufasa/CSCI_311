//CSCS 311
//Chinmay Satpanthi
//PriortyQ.h

#ifndef PRIORITYQ_H
#define PRIORITYQ_H

#include <list>
#include <vector>
#include <queue>
#include "Airplane.h"

using namespace std;

class PriorityQ{
			public:
						PriorityQ();			//default constructor
						
						void plane(int,int,string,string,int);				//adds the plane to approriate queue
	
						//data seek and adjust functions
						bool empty();
						int size();
						int peek(queue<Airplane>);
						int timeStamps();
						void popPlane(queue<Airplane> &poped);				//pops the desired plane
						void updateFuel();
						void fuelThis(queue<Airplane> &);

						//returns queue 
						queue<Airplane> get_high_priority();
						queue<Airplane> get_high_priority_dep();
						queue<Airplane> get_medium_priority();
						queue<Airplane> get_low_priority();
						queue<Airplane> get_departure();

						//printing functions
						void getPlane(char);						
						void printSimulation(vector<Airplane>,int);
						void printSimulation(int);
						void printRunways();
						void printData(queue<Airplane>);
						
			private:
						//queue variables 
						queue<Airplane> high_priority;
						queue<Airplane> high_priority_dep;
						queue<Airplane> medium_priority;
						queue<Airplane> low_priority;
						queue<Airplane> departure;
						
};


#endif // !PRIORITYQ_H


//CSCS 311
//Chinmay Satpanthi
//PriortyQ.cpp

#include <iostream>
#include <vector>
#include <list>
#include <math.h>
#include "PriorityQ.h"

//default constructor
PriorityQ::PriorityQ()
{
			
}

//add the plane to the queue
void PriorityQ::plane(int time, int id, string stat, string emg, int fuel)
{
			if (stat == "departing") {
						if (emg == "true") {
									high_priority_dep.push(Airplane(time, id, stat, emg, fuel));
						}
						else {
									departure.push(Airplane(time, id, stat, emg, fuel));
						}
			}
			else if (stat == "arriving") {
						if (emg == "true" || fuel == 0) {
									high_priority.push(Airplane(time, id, stat, emg, fuel));
						}
						else if (emg == "false" && fuel < 3) {
									medium_priority.push(Airplane(time, id, stat, emg, fuel));
						}
						else {
									low_priority.push(Airplane(time, id, stat, emg, fuel));
						}
			}
}

//checks if queue is empty
bool PriorityQ::empty()
{
			if (high_priority.empty() && high_priority_dep.empty() &&
						medium_priority.empty() && low_priority.empty() &&
						departure.empty()) {
						return true;
			}
			else {
						return false;
			}
}

//returns queue size
int PriorityQ::size()
{
			return high_priority.size() + high_priority_dep.size()+
						medium_priority.size() + low_priority.size() + departure.size();
}

//returns first value of qu
int PriorityQ::peek(queue<Airplane> que)
{
			if (que.empty()) {
						return 0;
			}
			return que.front().get_time();
}

//finds the smallest time in the queues
int PriorityQ::timeStamps()
{
			int val = -1;
			vector<int> findmin;
			
			findmin.push_back(peek(high_priority));
			findmin.push_back(peek(high_priority_dep));
			findmin.push_back(peek(medium_priority));
			findmin.push_back(peek(low_priority));
			findmin.push_back(peek(departure));

			for (int i = 0; i < findmin.size(); i++) {
						if (findmin[i] >= val) {
									val = findmin[i];
						}
			}
			for (int i = 0; i < findmin.size(); i++) {
						if (findmin[i] != 0 && findmin[i] <= val) {
									val = findmin[i];
						}
			}
			return val;
}

//pops the plane in que
void PriorityQ::popPlane(queue<Airplane> &poped)
{
			poped.pop();
}

//updates the fuel of planes
void PriorityQ::updateFuel()
{
			fuelThis(high_priority);
			fuelThis(medium_priority);
			fuelThis(low_priority);
}

void PriorityQ::fuelThis(queue<Airplane> &plane) {
			for (int i = 0; i < plane.size(); i++) {
						plane.front().set_fuel();
						if (plane.front().get_emergency() == "true"){
									plane.push(plane.front());
									popPlane(plane);
						}
						else if (plane.front().get_fuel() <= 0) {
									plane.front().set_emergency();
									high_priority.push(plane.front());
									popPlane(plane);
						}
						else if (plane.front().get_fuel() == 2) {
									medium_priority.push(plane.front());
									popPlane(plane);
						}
						else {
									plane.push(plane.front());
									popPlane(plane);
						}
			}
}

//get the queue variables
queue<Airplane> PriorityQ::get_high_priority()
{
			return high_priority;
}

queue<Airplane> PriorityQ::get_high_priority_dep()
{
			return high_priority_dep;
}

queue<Airplane> PriorityQ::get_medium_priority()
{
			return medium_priority;
}

queue<Airplane> PriorityQ::get_low_priority()
{
			return low_priority;
}

queue<Airplane> PriorityQ::get_departure()
{
			return departure;
}

//finds the right plane for the runway
void PriorityQ::getPlane(char a_or_b)
{
			if (a_or_b == 'A') {
						if (!high_priority_dep.empty()) {
									printData(high_priority_dep);
									popPlane(high_priority_dep);
						}
						else if (high_priority.size() >= 2) {
									printData(high_priority);
									popPlane(high_priority);
						}
						else if (!departure.empty()) {
									printData(departure);
									popPlane(departure);
						}
						else if (!medium_priority.empty()) {
									printData(medium_priority);
									popPlane(medium_priority);
						}
						else if (low_priority.size() >= 2){
									printData(low_priority);
									popPlane(low_priority);
						}
						else {
									printf("\n");
						}
			}
			else {
						if (!high_priority.empty()) {
									printData(high_priority);
									popPlane(high_priority);
						}
						else if (!medium_priority.empty()) {
									printData(medium_priority);
									popPlane(medium_priority);
						}
						else if (!high_priority_dep.empty()) {
									printData(high_priority_dep);
									popPlane(high_priority_dep);
						}
						else if (!low_priority.empty()){
									printData(low_priority);
									popPlane(low_priority);
						}
						else if (!departure.empty()) {
									printData(departure);
									popPlane(departure);
						}
						else {
									printf("\n");
						}
			}
}

//prints the new planes
void PriorityQ::printSimulation(vector<Airplane> new_entries, int timeTick)
{
			cout << "Time step " << timeTick << endl;
			printf("\t Entering Simulation\n");
			for (int i = 0; i < new_entries.size(); i++) {
						printf("\t\t %i %i %s %s %i \n",
									new_entries[i].get_time(),
									new_entries[i].get_id(),
									new_entries[i].get_status().c_str(),
									new_entries[i].get_emergency().c_str(),
									new_entries[i].get_fuel());
			}
}

//prints the empty simulator
void PriorityQ::printSimulation(int timeTick)
{
			cout << "Time step " << timeTick << endl;
			printf("\t Entering Simulation\n");
}

//prints the runways
void PriorityQ::printRunways()
{
			printf("\t Runway A \n");
			getPlane('A');
			printf("\t Runway B \n");
			getPlane('B');
			if (size() > 0) {
						updateFuel();
			}
			
}

//pritns the plane data
void PriorityQ::printData(queue<Airplane> plane)
{
			printf("\t\t %i %i %s %s %i \n",
						plane.front().get_time(),
						plane.front().get_id(),
						plane.front().get_status().c_str(),
						plane.front().get_emergency().c_str(),
						plane.front().get_fuel());
}

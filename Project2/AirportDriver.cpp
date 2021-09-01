// Project2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//CSCS 311
//Chinmay Satpanthi
//AirportDriver.cpp

#include <iostream>
#include "PriorityQ.h"
#include "Airplane.h"

using namespace std;


int main()
{
   /*
   Initializing varibles
   */
   PriorityQ * PQ = new PriorityQ();      
   vector<Airplane> new_entries;

   int timeStamp = -1;
   int nextPlane = -1;
   int planeId = -1;
   string planeStatus = "";
   string planeEmergency = ""; 
   int planeFuel = -1;
   int timeTick = -1;

   /*
   checks initial input to see where to start
   */
   cin >> timeStamp;
   if (timeStamp == -1) {
      return 0;
   }
   cin >> planeId >> planeStatus >> planeEmergency >> planeFuel;

   PQ->plane(timeStamp, planeId, planeStatus, planeEmergency, planeFuel);   
   new_entries.push_back(Airplane(timeStamp, planeId, planeStatus, planeEmergency, planeFuel));
   timeTick = timeStamp;

   cin >> timeStamp;

   bool flag = true;

   /*
   here we get variables from the terminal/file and add to PQ
   */
   while (flag) {
      
      /*
      this if is when we are done with inputs and therefore we clear out all the
      remaining planes
      */
      if (timeStamp == -1) {
         while (!PQ->empty()) {
            if (!new_entries.empty() && timeTick == new_entries.front().get_time()) {
               PQ->printSimulation(new_entries,timeTick);
               PQ->printRunways(); 
               new_entries.clear();
            }
            else if (PQ->timeStamps() < timeTick){
               PQ->printSimulation(timeTick);
               PQ->printRunways();
            }
            timeTick++;

         }
         flag = false;
      }                                         //This else if adds plane of same time step
      else if (timeStamp == timeTick){
         cin >> planeId >> planeStatus >> planeEmergency >> planeFuel;  
         PQ->plane(timeStamp, planeId, planeStatus, planeEmergency, planeFuel);
         new_entries.push_back(Airplane(timeStamp, planeId, planeStatus, planeEmergency, planeFuel));
         cin >> timeStamp;
      }                                         //This else notes that we have a new time step so
                                                //we can analyze the planes we have now                 
      else if (timeStamp != timeTick) {  
         if (!new_entries.empty() && timeTick == new_entries.front().get_time()) {
            PQ->printSimulation(new_entries, timeTick);        //prints the new planes
            PQ->printRunways();                                //prints the runway details
            new_entries.clear();

         }
         else if (PQ->timeStamps() < timeTick && !PQ->empty()){
            PQ->printSimulation(timeTick);            //empty simulation
            PQ->printRunways();        //prints the runway details
         }  
         
         timeTick++;
      }
      
   }
   return 0;
}

 
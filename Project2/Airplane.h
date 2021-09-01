//CSCS 311
//Chinmay Satpanthi
//Airplane.h

#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <list>
#include <vector>
#include <queue>

using namespace std;

class Airplane {
			public:
						Airplane(int,int,string,string,int);						//constructor
						
						//getter functions
						int get_time();
						int get_id();
						string get_status();
						string get_emergency();
						int get_fuel();
						
						void set_fuel();
						void set_emergency();
						
			private:
						//variables
						int time_step = 0;
						int plane_id = 0;
						string status = "";
						string emergency = "";
						int fuel = 0;
};


#endif // !AIRPORT_H

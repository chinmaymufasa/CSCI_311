//CSCS 311
//Chinmay Satpanthi
//Airplane.cpp

#include <iostream>
#include <vector>
#include <list>
#include <math.h>
#include "Airplane.h"

/*
constructor
*/

Airplane::Airplane(int time_s, int plane_i, string plane_stat, string plane_emg, int plane_fuel)
{
			time_step = time_s;
			plane_id = plane_i;
			status = plane_stat;
			emergency = plane_emg;
			fuel = plane_fuel;
}

//returns time
int Airplane::get_time()
{
			return time_step;
}

//returns plane id
int Airplane::get_id()
{
			return plane_id;
}

//returns status of arrival or takeoff
string Airplane::get_status()
{
			return status;
}

//emergency check
string Airplane::get_emergency()
{
			return emergency;
}

//fuel value
int Airplane::get_fuel()
{
			return fuel;
}

void Airplane::set_fuel()
{
			if (fuel != 0) {
						fuel--;
			}
}

void Airplane::set_emergency()
{
			emergency = "true";
}



// CSCI 311 - Spring 2021
// Graph class cpp
// Chinmay Satpanthi

#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

#include "Graph.h"

using namespace std;

/*
Constructor
*/
Graph::Graph() {
			source = -1;
			destination = -1;
			max_charge = -1;
}


/*
adds the values to the graph and defines the edges
*/
void Graph::setMap() {
			unsigned int n = 0, m = 0, c = 0, x = 0;
			cin >> n >> m >> c >> x;
			cin >> source >> destination;
			if (source == destination) {											//check if end is start
						exit(0);
			}

			max_charge = x;
			for (unsigned int i = 0; i < n; i++) { //adds the vertexes and if they have a charging station
						int a = -1, g = -1;
						cin >> a >> g;

						Node v(a);
						nodes.push_back(v);
						if (g) {
									nodes[a].charge_station = true;		//sets true for charging stations
						}
			}

			nodes[source].current_charge = c;						//current car range

			for (unsigned int i = 0; i < m; i++) {
						unsigned int u = -1, v = -1, w = -1;
						cin >> u >> v >> w;

						if (w <= c) {
									nodes[u].neighbors.push_back(&nodes[v]);								//adds not weighted edges
									nodes[v].neighbors.push_back(&nodes[u]);
									nodes[u].weights.push_back(make_pair(w, v));				//adds the weights
									nodes[v].weights.push_back(make_pair(w, u));

						}
			}
			Dijkstra(source);																																					//calls Dijkstra's function
}


/*
Dijkstras algorithm
*/
void Graph::Dijkstra(int s) {
			for (unsigned int i = 0; i < nodes.size(); i++) {    //initializes all values
						nodes[i].dist = INT_MAX;
						nodes[i].predecessor = NULL;
			}

			priority_queue<pair<int, int>, vector < pair<int, int> >, greater< pair<int, int> > > Q;   //priority queue

			Q.push(make_pair(0, s));																																													//adds source pair

			nodes[s].dist = 0;																																																			//sets default node to 0
			nodes[s].nodes_visit = 0;

			while (!Q.empty() && Q.top().second != destination) {                //checks all queue values

						int u = Q.top().second;																																										 //u is first element in priority q set 
						Q.pop();	

						for (unsigned int i = 0; i < nodes[u].neighbors.size(); i++)
						{
									int v = nodes[u].weights[i].second;																											 //gets the neighbor v value	
									int weight = nodes[u].weights[i].first;																								//gets the weight between vertexes

									if (weight > nodes[u].current_charge && v == destination) {				//cant pass through this point
												nodes[u].dist = INT_MAX;
												//cout << "Will run out of charge" << endl;
									}                                                              
									else if (nodes[v].dist > nodes[u].dist + weight)															//**Relaxation portion**
									{

												nodes[v].dist = nodes[u].dist + weight;																					//if u is shorter path, update path distance
												nodes[v].predecessor = &nodes[u];
												nodes[v].nodes_visit = nodes[u].nodes_visit + 1;												//counts predecessors

												if (nodes[v].charge_station) {																														//recharge car if at station
															nodes[v].current_charge = max_charge;
												}
												else {
															nodes[v].current_charge = nodes[u].current_charge - weight;
												}
												Q.push(make_pair(nodes[v].dist, v));																								//add the new pair to queue
									}
									else if (v == destination) {
												nodes[u].destination_dist = nodes[u].dist + weight;									//destination local distances
									}

						}
			}

}

/*
This function prints out the route
*/

void Graph::printRoute()
{
			vector<int> route;
			vector<int> dist;
			int ID = nodes[destination].id;
			if (nodes[destination].dist == INT_MAX) {
						cout << "No suitable path from start to end" << endl;							  //if no path 
			}
			else if (nodes[destination].neighbors.size() > 1) {												  //if there is a tie check neighbors for preferable path

						int min_distance = nodes[destination].dist;																	  //fewer stops
						for (unsigned int i = 0; i < nodes[destination].neighbors.size(); i++) {
									if (nodes[destination].neighbors[i] != nodes[destination].predecessor && nodes[destination].neighbors[i]->dist != INT_MAX) {
												if (nodes[destination].neighbors[i]->destination_dist == min_distance) {
															dist.push_back(nodes[destination].neighbors[i]->id); //same number fo stops ties
												}
									}
						}
						if (dist.size() > 0) {																																									//checks all same length paths
									int min_visits = nodes[dist[0]].nodes_visit;
									vector<int> sz;
									for (unsigned int i = 1; i < dist.size() - 1; i++) {
												if (nodes[dist[i]].nodes_visit <= min_visits) {
															if (nodes[dist[i]].nodes_visit == min_visits) {	
																		sz.push_back(nodes[dist[i]].id);																			
															}
															else {
																		min_visits = nodes[dist[i]].nodes_visit;											//looks for one with least paths
																		ID = nodes[dist[i]].id;
																		sz.clear();
															}
												}
									}
						}
						if (ID == destination) {																																							//print this if no ties
									cout << nodes[ID].dist << ": ";
									route.push_back(nodes[ID].id);
									for (int i = 1; i < nodes[destination].nodes_visit; i++) {
												ID = nodes[ID].predecessor->id;
												route.push_back(nodes[ID].id);
									}
									route.push_back(nodes[source].id);
						}
						else {																																																									//print this if ties are found
									cout << nodes[destination].dist << ": ";
									route.push_back(nodes[destination].id);
									for (int i = 1; i < nodes[ID].nodes_visit; i++) {
												ID = nodes[ID].predecessor->id;
												route.push_back(nodes[ID].id);
									}
									route.push_back(nodes[source].id);
						}

			}
			else {
						cout << nodes[destination].dist << ": ";																							//if no neighbors 
						route.push_back(nodes[destination].id);
						for (int i = 1; i < nodes[destination].nodes_visit; i++) {
									ID = nodes[ID].predecessor->id;
									route.push_back(nodes[ID].id);
						}
						route.push_back(nodes[source].id);
			}
			for (int i = route.size() - 1; i >= 0; i--) {																					//print the vector
						cout << route[i] << " ";
			}
			cout << endl;
}



#include "Graph.hpp"
#include "Traveling_Salesman.hpp"
#include <climits>
#include <iostream>


Road::Road(string start, string end, int distance){
    this->start = start;
    this->end = end;
    this->distance = distance;
}


Graph::Graph(int numCities, int numRoads){
    this->numCities = numCities;
    this->numRoads = numRoads;

    this->cities = unordered_map<string,vector<Road>>(numCities);
}

Graph::~Graph(){
}

unordered_map<string,vector<Road>> Graph::getCities(){
    return this->cities;
}

int Graph::getNumCities(){
    return this->numCities;
}

int Graph::getNumRoads(){
    return this->numRoads;
}

// Add a road to both the start and end cities, as roads are bidirectional
void Graph::addRoad(string start, string end, int distance){
    this->cities[start].push_back(Road(start, end, distance));
    this->cities[end].push_back(Road(end, start, distance));
}

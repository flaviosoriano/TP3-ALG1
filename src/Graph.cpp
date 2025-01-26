#include "Graph.hpp"

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
    // Nothing to do here
}
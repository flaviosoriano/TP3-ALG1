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

// Add a road to both the start and end cities, as roads are bidirectional
void Graph::addRoad(string start, string end, int distance){
    this->cities[start].push_back(Road(start, end, distance));
    this->cities[end].push_back(Road(end, start, distance));
}
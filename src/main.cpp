#include "Graph.hpp"
#include <iostream>

int main(){

    int numCities = 0, numRoads = 0;
    std::cin >> numCities >> numRoads;

    Graph graph(numCities, numRoads);

    for (int i = 0; i < numRoads; i++){
        std::string start, end;
        int distance;
        std::cin >> start >> end >> distance;
        graph.addRoad(start, end, distance);
    }

    graph.BruteForce();
    

    return 0;
}
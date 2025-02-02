#include "Graph.hpp"
#include "Traveling_Salesman.hpp"
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

    //Traveling_Salesman::BruteForce(graph);
    Traveling_Salesman::Greedy(graph);
    Traveling_Salesman::DynamicProgramming(graph);
    

    return 0;
}
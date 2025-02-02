#include "Graph.hpp"
#include "Traveling_Salesman.hpp"
#include <iostream>

int main(){

    int numCities = 0, numRoads = 0;
    char choosenMethod;
    std::cin >> choosenMethod;
    std::cin >> numCities >> numRoads;

    Graph graph(numCities, numRoads);

    for (int i = 0; i < numRoads; i++){
        std::string start, end;
        int distance;
        std::cin >> start >> end >> distance;
        graph.addRoad(start, end, distance);
    }

    switch (choosenMethod)
    {
    case 'b':
        Traveling_Salesman::BruteForce(graph);  
        break;

    case 'd':
        Traveling_Salesman::DynamicProgramming(graph);
        break;
        
    case 'g':
        Traveling_Salesman::Greedy(graph);
        break;

    default:
        break;
    }

    return 0;
}
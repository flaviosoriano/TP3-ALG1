#include "Algorithms.hpp"
#include <climits>
#include <utility>
#include "Graph.hpp"

int factorial(int n){
    if (n == 0){
        return 1;
    }
    return n * factorial(n-1);
}

void Algorithms::TestPermutation(Graph &graph, vector<string> &cityNames, vector<string> &currentPath, vector<string> &minPath, int &minDistance, int start, int end){
    // Base case for recursion
    if (start == end){
        int distance = 0;
        unordered_map<string, vector<Road>> cities = graph.getCities();
        for (int i = 0; i < graph.getNumCities() - 1; i++){
            for(auto road: cities[currentPath[i]]){
                if (road.end == currentPath[i+1]){
                    distance += road.distance;
                    break;
                }
            }
        }
        // Add the distance from the last city back to the first city
        string lastCity = currentPath[currentPath.size()-1];
        string firstCity = currentPath[0];
        for(auto road: cities[lastCity]){
            if (road.end == firstCity){
                distance += road.distance;
                break;
            }
        }
        if (distance < minDistance){
            minDistance = distance;
            minPath = currentPath;
        }
    }
    else{
        for (int i = start; i < end; i++){
            swap(cityNames[start], cityNames[i]);
            TestPermutation(graph, cityNames, currentPath, minPath, minDistance, start+1, end);
            swap(cityNames[start], cityNames[i]);
        }
    }
}

pair<vector<string>, int> Algorithms::BruteForce(Graph &graph){
    int minDistance = INT_MAX;
    vector<string> minPath;

    // Get all permutations of the cities
    vector<string> cityNames;
    for (auto city : graph.getCities()){
        cityNames.push_back(city.first);
    }
    TestPermutation(graph, cityNames, cityNames, minPath, minDistance, 0, (int)cityNames.size()-1);

    return make_pair(minPath, minDistance);
}
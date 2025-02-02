#include "Traveling_Salesman.hpp"
#include <climits>
#include <utility>
#include <iostream>
#include "Graph.hpp"
#include <math.h>

int factorial(int n){
    if (n == 0){
        return 1;
    }
    return n * factorial(n-1);
}

void Traveling_Salesman::printMinPath(vector<string> minPath, int minPathDist){
    cout << minPathDist << endl;
    for(auto city : minPath){
        cout << city << " ";
    }
    cout << endl;
}

/*
    Recursive function to test all permutations of the cities
    and find the shortest path

    @param Graph &graph: The graph object
    @param vector<string> &cityNames: The list of city names
    v@param ector<string> &currentPath: The current path being tested
    @param vector<string> &minPath: The shortest path found so far
    @param int &minDistance: The shortest distance found so far
    @param int start: The start index of the permutation
    @param int end: The end index of the permutation
*/
void Traveling_Salesman::TestPermutation(Graph &graph, vector<string> &cityNames, vector<string> &currentPath, vector<string> &minPath, int &minDistance, int start, int end){
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

/*
    Brute Force Method - Test all permutations of the cities
    @param Graph &graph: A complete graph of cities and roads
*/
void Traveling_Salesman::BruteForce(Graph &graph){
    int minDistance = INT_MAX;
    vector<string> minPath;

    // Get all permutations of the cities
    vector<string> cityNames;
    for (auto city : graph.getCities()){
        cityNames.push_back(city.first);
    }
    TestPermutation(graph, cityNames, cityNames, minPath, minDistance, 0, (int)cityNames.size()-1);

    printMinPath(minPath, minDistance);
}


int Cost(int mask, int addPosition, int n, vector<vector<int>> &graphMatrix, vector<vector<int>> &dpMatrix, vector<vector<int>>& parentMatrix){

    //If all cities were visited
    if(mask == (1 << n)-1){
        return graphMatrix[addPosition][0];
    }
    
    if(dpMatrix[mask][addPosition] != -1){
        return dpMatrix[mask][addPosition];
    }

    int minCost = INT_MAX;
    int bestNextCity = -1;

    for(int city = 0; city < n; city++){
        //if city were not visited
        if((mask & (1 << city)) == 0){
            int newMask = mask | (1 << city);
            int newCost = graphMatrix[addPosition][city] + Cost(newMask, city, n, graphMatrix, dpMatrix, parentMatrix);

            if(newCost < minCost){
                minCost = newCost;
                bestNextCity = city;
            }
        }
    }

    parentMatrix[mask][addPosition] = bestNextCity;
    dpMatrix[mask][addPosition] = minCost;
    return dpMatrix[mask][addPosition];
}



void Traveling_Salesman::DynamicProgramming(Graph &graph){

    unordered_map<string, vector<Road>> cities = graph.getCities();
    int n = graph.getNumCities();

    // Index the cities, needed to use a mask in the cost Matrix
    unordered_map<string, int> cityToIndex;
    vector<string> indexToCity(n);
    int index = 0;
    for(auto city : cities){
        cityToIndex[city.first] = index;
        indexToCity[index] = city.first;
        index++;
    }
    // Build a graph Matrix
    vector<vector<int>> graphMatrix(n, vector<int>(n, 0));
    for(auto city : cities){
        for(auto road : city.second){
            int startIndex = cityToIndex[road.start];
            int endIndex = cityToIndex[road.end];
            graphMatrix[startIndex][endIndex] = road.distance;
            graphMatrix[endIndex][startIndex] = road.distance;
        }
    }

    vector<vector<int>> dpMatrix((int)pow(2, n), vector<int>(n, -1));
    vector<vector<int>> parentMatrix((int)pow(2, n), vector<int>(n, -1));


    for(int i = 1; i < n; i++){
        dpMatrix[1 << i][i] = graphMatrix[0][i];
    }

    int mask = 1;
    int minCost = Cost(1, 0, n, graphMatrix, dpMatrix, parentMatrix);

    mask = 1;
    int position = 0;

    vector<string> path;
    path.push_back(indexToCity[0]);
    while(true){
        int nextCity = parentMatrix[mask][position];
        if(nextCity == -1) break;

        path.push_back(indexToCity[nextCity]);
        mask = mask | (1 << nextCity);
        position = nextCity;
    }   
    printMinPath(path, minCost);
}

/*
    Nearest Neighbor Method
    @param Graph &graph: A complete graph of cities and roads
*/
void Traveling_Salesman::Greedy(Graph &graph){

    unordered_map<string, vector<Road>> cities = graph.getCities();
    vector<string> shortestPath;
    int distance = 0;

    string startCity = cities.begin()->first;
    shortestPath.push_back(startCity);

    unordered_map<string, bool> visited;   
    for (auto city : cities){
        visited[city.first] = false;
    }
    visited[startCity] = true;
    
    // Find the nearest neighbor for each city
    string currentCity = startCity;
    for(int i = 0; i < graph.getNumCities()-1; i++){
        int minDistance = INT_MAX;
        string nextCity;
        for (auto road : cities[currentCity]){
            if (road.distance < minDistance && !visited[road.end]){
                minDistance = road.distance;
                nextCity = road.end;
            }
        }
        shortestPath.push_back(nextCity);
        visited[nextCity] = true;
        distance += minDistance;
        currentCity = nextCity;
    }

    // Add the distance from the last city back to the first city
    string lastCity = shortestPath[shortestPath.size()-1];
    int lastRoadDistance = 0;
    for (auto road : cities[lastCity]){
        if (road.end == startCity){
            lastRoadDistance = road.distance;
            break;
        }
    }
    distance += lastRoadDistance;

   printMinPath(shortestPath, distance);
}
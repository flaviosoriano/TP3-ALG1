#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

struct Road{
    string start;
    string end;
    int distance;

    Road(string start, string end, int distance);
};

class Graph{
private:
    unordered_map<string,vector<Road>> cities; // used to maintain O(1) access to cities
    int numCities;
    int numRoads;
public:
    Graph(int numCities, int numRoads);
    ~Graph();

    void addRoad(string start, string end, int distance);
};


#endif // GRAPH_HPP
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>

using namespace std;

struct Road;

struct City{
    string name;
    vector<Road*> roads;
};

struct Road{
    City* start;
    City* end;
    int distance;
};


class Graph{
private:
    vector<City> cities;
public:

    Graph(/* args */);
    ~Graph();
};

Graph::Graph(/* args */){
}

Graph::~Graph(){
}







#endif // GRAPH_HPP
#ifndef Traveling_Salesman_HPP
#define Traveling_Salesman_HPP

#include <utility>
#include <vector>
#include <string>

using namespace std;

class Graph;

class Traveling_Salesman
{
private:
    // Utility functions
    static void printMinPath(vector<string> minPath, int minPathDist);
    static void TestPermutation(Graph &graph, vector<string> &cityNames, vector<string> &currentPath, vector<string> &minPath, int &minDistance, int start, int end);
    static int Cost(int mask, int addPosition, int n, vector<vector<int>> &graphMatrix, vector<vector<int>> &dpMatrix, vector<vector<int>>& parentMatrix);
public:
    // Methods to solve the Traveling salesman problem
    static void BruteForce(Graph &graph); // Try every permutation of cities and choose the one with the smallest total distance
    static void DynamicProgramming(Graph &graph); // Held-Karp Algorithm
    static void Greedy(Graph &graph); // Nearest Neighbor Method
};


#endif // Traveling_Salesman_HPP

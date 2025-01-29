#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <utility>
#include <vector>
#include <string>

using namespace std;

class Graph;

class Algorithms
{
private:
    static void TestPermutation(Graph &graph, vector<string> &cityNames, vector<string> &currentPath, vector<string> &minPath, int &minDistance, int start, int end);
public:
    static pair<vector<string>, int> BruteForce(Graph &graph);

};


#endif // ALGORITHMS_HPP

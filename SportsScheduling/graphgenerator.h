#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include <vector>

using namespace std;

class GraphGenerator
{
public:
    GraphGenerator();
    vector<vector<int>> buildGraph(int n, bool shuffle_flag = true);
    vector<vector<int>> buildOddGraph(int n);
    vector<vector<int>> buildEvenGraph(int n);
};

#endif // GRAPHGENERATOR_H

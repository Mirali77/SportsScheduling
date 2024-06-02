#include "graphgenerator.h"
#include <cmath>
#include <random>
#include <numeric>
#include <algorithm>

GraphGenerator::GraphGenerator()
{

}

vector<vector<int>> GraphGenerator::buildGraph(int n, bool shuffle_flag)
{
    vector<vector<int>> graph;
    if (n == 0) return graph;
    if (n & 1) graph = buildOddGraph(n);
    else graph = buildEvenGraph(n);
    vector<vector<int>> res = graph;
    if (shuffle_flag) {
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        random_device rd;
        mt19937 gen(rd());
        shuffle(p.begin(), p.end(), gen);
        for(int i = 0; i < n; i++) for(int j = i + 1; j < n; j++) res[min(p[i], p[j])][max(p[i], p[j])] = graph[i][j];
    }
    return res;
}

vector<vector<int>> GraphGenerator::buildOddGraph(int n)
{
    vector<vector<int>> graph(n, vector<int>(n));
    auto dec = [&](int i) { return (i - 1 + n) % n;};
    auto inc = [&](int i) { return (i + 1) % n;};
    auto dist = [&](int i, int j) { return min(abs(i - j), n - abs(i - j));};
    for(int i = 0; i < n; i++) {
        int l = dec(i), r = inc(i);
        while (true) {
            graph[min(l, r)][max(l, r)] = i + 1;
            if (dist(l, r) == 1) break;
            l = dec(l), r = inc(r);
        }
    }
    return graph;
}

vector<vector<int>> GraphGenerator::buildEvenGraph(int n)
{
    vector<vector<int>> graph = buildOddGraph(n - 1);
    graph.push_back(vector<int>(n));
    for(int i = 0; i < n - 1; i++) graph[i].push_back(0);
    for(int i = 0; i < n - 1; i++) {
        int j = n - 1;
        vector<int> used(n);
        for(int j = 0; j < n - 1; j++) {
            if (j == i) continue;
            used[graph[min(i, j)][max(i, j)]] = 1;
        }
        for(int col = 1; col < n; col++) {
            if (used[col] == 0) {
                graph[min(i, j)][max(i, j)] = col;
                break;
            }
        }
    }
    return graph;
}

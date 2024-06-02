#ifndef MCMFMANAGER_H
#define MCMFMANAGER_H

#include <vector>
#include <functional>
#include <queue>
using namespace std;

using ll = long long;
#define sz(a) (int)(a.size())
#define fst first
#define snd second

class MCMFManager
{
private:
    struct Edge {
        int from, to;
        ll cost, cap;
        Edge(int from, int to, ll cap, ll cost) : from(from), to(to), cost(cost), cap(cap) {}
    };
    int n; ll inf;
    vector<Edge> edg;
    vector<vector<int>> adj;
    vector<ll> pot, dist;
    vector<bool> used;
    vector<int> from;
public:
    MCMFManager(int sn, ll c_inf);
    void add_edge(int from, int to, ll cap, ll cost);
    void init(int s);
    ll calc(int s, int t, ll k = -1);
    vector<pair<pair<int, int>, ll>> getEdges();
};

#endif // MCMFMANAGER_H

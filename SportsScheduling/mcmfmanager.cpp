#include "mcmfmanager.h"

MCMFManager::MCMFManager(int sn, ll c_inf) { n = sn; inf = c_inf; adj.resize(n); pot.resize(n); dist.resize(n); used.resize(n); from.resize(n, -1); }

void MCMFManager::add_edge(int from, int to, ll cap, ll cost)
{
    int k = sz(edg);
    edg.push_back(Edge(from, to, cap, cost));
    edg.push_back(Edge(to, from, 0, -cost));
    adj[from].push_back(k);
    adj[to].push_back(k ^ 1);
}

void MCMFManager::init(int s)
{
    function<ll(int)> dfs = [&](int v) {
        if (used[v]) return dist[v];
        used[v] = true;
        if (v == s) return dist[v] = pot[v] = 0;
        dist[v] = pot[v] = inf;
        for(auto to: adj[v]) if (to & 1) {
            ll cand = dfs(edg[to].to) - edg[to].cost;
            if (cand < dist[v]) dist[v] = pot[v] = cand, from[v] = to ^ 1;
        }
        return dist[v];
    };
    for(int i = 0; i < n; i++) dfs(i);
}

ll MCMFManager::calc(int s, int t, ll k)
{
            bool f = true;
            init(s);
            ll ans = 0;
            while (k--) {
                if (!f) {
                    used.assign(n, false), from.assign(n, -1), dist.assign(n, inf);
                    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
                    pq.push({ dist[s] = 0, s });
                    while (sz(pq)) {
                        int h = pq.top().snd;
                        pq.pop();
                        used[h] = true;
                        for(auto to: adj[h]) {
                            if (edg[to].cap == 0 || used[edg[to].to]) continue;
                            if (dist[edg[to].to] > dist[h] + edg[to].cost + pot[h] - pot[edg[to].to]) {
                                dist[edg[to].to] = dist[h] + edg[to].cost + pot[h] - pot[edg[to].to];
                                from[edg[to].to] = to;
                                pq.push({ dist[edg[to].to], edg[to].to });
                            }
                        }
                    }
                    for(int i = 0; i < n; i++) dist[i] -= pot[s] - pot[i];
                    for(int i = 0; i < n; i++) pot[i] = dist[i];
                }
                f = false;
                if (!used[t]) break;
                int pos = t;
                while (pos != s) {
                    edg[from[pos]].cap--;
                    edg[from[pos] ^ 1].cap++;
                    ans += edg[from[pos]].cost;
                    pos = edg[from[pos]].from;
                }
            }
            return ans;
}

vector<pair<pair<int, int>, ll>> MCMFManager::getEdges()
{
    vector<pair<pair<int, int>, ll>> res;
    for(int i = 1; i < edg.size(); i += 2) {
        if (edg[i].from == n - 1 || edg[i].to == 0 || edg[i].cap == 0) continue;
        res.push_back({{edg[i].to, edg[i].from}, edg[i].cap});
    }
    return res;
}

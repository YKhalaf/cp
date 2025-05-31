#include <bits/stdc++.h>
using namespace std;

vector<int> dep;
vector<vector<int> > adj, up;

void dfs_lca(int u, int p) {
    up[u][0] = p;
    for (int bit = 1; bit < 18; bit++) {
        up[u][bit] = (up[u][bit - 1] < 0 ? -1 : up[up[u][bit - 1]][bit - 1]);
    }
    for (int v: adj[u]) {
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        dfs_lca(v, u);
    }
}

int kth(int u, int k) {
    for (int bit = 0; bit < 18; bit++) {
        if (k >> bit & 1) u = up[u][bit];
    }
    return u;
}

int lca(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    v = kth(v, dep[v] - dep[u]);
    if (u == v) return u;
    for (int bit = 17; bit >= 0; bit--) {
        if (up[u][bit] != up[v][bit]) {
            u = up[u][bit];
            v = up[v][bit];
        }
    }
    return up[u][0];
}

int dist(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}

#include <bits/stdc++.h>
#define st first
#define nd second
#define mk std::make_pair

/*
Clearing the lowest 1 bit: x & (x - 1), all trailing 1’s: x & (x + 1)
Setting the lowest 0 bit: x | (x + 1)
Enumerating subsets of a bitmask m: x=0; do { ...; x=(x+1+˜m)&m; } while (x!=0);
__builtin_ctz/__builtin_clz returns the number of trailing/leading zero bits.
__builtin_popcount(unsigned x) counts 1-bits (slower than table lookups). */

// ======== CENTROID-DECOMPOSITION by Piotr Bejda ========
// usage: decompose(any vertex, 0, 0)
const int MAXN = 100010;
std::vector<int> edges[MAXN]; // input
bool taken[MAXN]; // input, = 0 before start
int size[MAXN]; // auxiliary
int jump[MAXN]; // output: parent
int depth[MAXN]; // output: layer
int dist[20][MAXN]; // output: dist from ancestor at given depth

void update_size(int u) {
    taken[u] = 1;
    size[u] = 1;
    for (int v : edges[u]) if(!taken[v]){
        update_size(v);
        size[u] += size[v];
    }
    taken[u] = 0;
}

std::pair<int, int> centroid(int u, int n) {
    taken[u] = 1;
    std::pair<int, int> r = mk(n-size[u], u);
    for(int v : edges[u]) if(!taken[v]) r.st = std::max(r.st, size[v]);
    for(int v : edges[u]) if(!taken[v]) r = std::min(r, centroid(v, n));
    taken[u] = 0;
    return r;
}

void fill_dist(int u, int d, int layer){
    taken[u] = 1;
    dist[layer][u] = d;
    for(int v : edges[u]) if(!taken[v]) fill_dist(v, d+1, layer);
    taken[u] = 0;
}

void decompose(int u, int p, int layer){
    update_size(u);
    int n = size[u];
    u = centroid(u, n).nd;
    jump[u] = p;
    depth[u] = layer;
    fill_dist(u, 0, layer);
    taken[u] = 1;
    for (int v : edges[u]) if(!taken[v]) decompose(v, u, layer+1);
}
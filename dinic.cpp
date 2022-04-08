#include <bits/stdc++.h>
#define ll long long
#define mk std::make_pair
#define st first
#define nd second
 
/*
 * Check whether you should change flows for long long! 
 * MAX_N is graph size (vertices)
 * residual edges should be next to original
 */

const int inf = INT_MAX / 2;
 
struct Edge {
    int f, cap;
    Edge(int F, int CAP) : f(F), cap(CAP) {}
};

const int MAX_N = 205;
 
std::vector<Edge> e;
std::vector<std::pair<int, int> > list[MAX_N+3];
int n, m, N;
 
void input() {
    std::cin >> n >> m;
    N = n+m+2;
 
    for (int i = 0; i < N; i++)
        list[i].clear();
    e.clear();
 
    for (int i = 1; i <= n; i++) {
        int x; std::cin >> x;
        e.emplace_back(0, x);
        list[0].push_back(mk(i, e.size()-1));
        e.emplace_back(0, 0);
        list[i].push_back(mk(0, e.size()-1));
    }
 
    for (int i = n+1; i <= n+m; i++) {
        int x; std::cin >> x;
        e.emplace_back(0, x);
        list[i].push_back(mk(N-1, e.size()-1));
        e.emplace_back(0, 0);
        list[N-1].push_back(mk(i, e.size()-1));
    }
 
    for (int i = 1; i <= n; i++) {
        for (int j = n+1; j <= n+m; j++) {
            int x; std::cin >> x;
            if (x) {
                e.emplace_back(0, inf);
                list[i].push_back(mk(j, e.size()-1));
                e.emplace_back(0, 0);
                list[j].push_back(mk(i, e.size()-1));
            }
        }
    }
}
 
int d[MAX_N+3];
 
bool bfs() {
    for (int i = 0; i < N; i++)
        d[i] = -1;
    d[0] = 0;
    std::queue<int> q;
    q.push(0);
 
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto p : list[v]) {
            if (e[p.nd].f < e[p.nd].cap && d[p.st] == -1) {
                d[p.st] = d[v] + 1;
                q.push(p.st);
            }
        }
    }
 
    return d[N-1] != -1;
}
 
int next[MAX_N+3];
 
int dfs(int v, int flow) {
    if (!flow)
        return 0;
    if (v == N-1)
        return flow;
 
    while (next[v] < list[v].size()) {
        int i = next[v];
        next[v]++;
 
        int u = list[v][i].st;
        int id = list[v][i].nd;
 
        if (d[u] != d[v]+1)
            continue;
 
        if (e[id].f < e[id].cap) {
            int new_flow = dfs(u, std::min(flow, e[id].cap - e[id].f));
            if (new_flow > 0) {
                e[id].f += new_flow;
                e[id^1].f -= new_flow;
                return new_flow;
            }
        }
    }
 
    return 0;
}
 
int dinic() {
    int flow = 0;
    while (bfs()) {
        for (int i = 0; i < N; i++)
            next[i] = 0;
        while (1) {
            int new_flow = dfs(0, inf);
            if (!new_flow)
                break;
            flow += new_flow;
        }
    }
    return flow;
}
 
void solve() {
    input();
    std::cout << dinic() << "\n";
}
 
int main() {
    std::ios_base::sync_with_stdio(0); std::cin.tie(NULL);
    int z;
    std::cin >> z;
    while (z--)
        solve();
}
#include <bits/stdc++.h>
 
/*
 * to find min vertex cover / max independent set
 * take visited on the left and not visited on the right
 * or make it the other way around (i dont remember)
 */

const int MAX_N = 3e3;
int n, m;
std::vector<int> list[MAX_N+3];
 
void input() {
    std::cin >> n >> m;
 
    for (int i = 0; i <= 2*n-1; i++)
        list[i].clear();
 
    for (int i = 1; i <= m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        list[2*u+1].push_back(2*v);
        list[2*v].push_back(2*u+1);
    }
    n*=2;
}
 
bool visited[MAX_N+3];
int mate[MAX_N+3];
 
bool path_dfs(int v) {
    visited[v] = true;
    for (auto u : list[v])
        if (mate[u] == -1 || (!visited[mate[u]] && path_dfs(mate[u]))) {
            mate[u] = v;
            mate[v] = u;
            return true;
        }
    return false;
}
 
bool find_paths() {
    for (int i = 0; i < n; i++)
        visited[i] = false;
    bool new_path = false;
    for (int i = 0; i < n; i += 2)
        if (mate[i] == -1 && !visited[i])
            if (path_dfs(i))
                new_path = true;
    return new_path;
}
 
int turbo_matching() {
    for (int i = 0; i < n; i++)
        mate[i] = -1;
    while (1)
        if (!find_paths())
            break;
 
    int match_size = 0;
    for (int i = 0; i < n; i += 2)
        if (mate[i] != -1)
            match_size++;
    return match_size;
}
 
void solve() {
    input();
    std::cout << ( (turbo_matching() == n/2) ? "TAK\n" : "NIE\n" );
}
 
int main() {
    std::ios_base::sync_with_stdio(0); std::cin.tie(NULL);
    int z;
    std::cin >> z;
    while (z--)
        solve();
}
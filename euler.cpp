#include <bits/stdc++.h>
#define st first
#define nd second
#define mk std::make_pair
 
const int MAX_M = 5e5;
const int MAX_N = 5e4;
std::vector<std::pair<int, int> > list[MAX_N+4];
bool used[MAX_M+MAX_N+3];
int deg[MAX_N+4];
int n, m;
std::vector<int> e;
 
void clear(){
    for (int i = 0; i <= n+1; i++){
        list[i].clear();
        deg[i] = 0;
    }
    for (int i = 0; i <= m+n+2; i++)
        used[i] = false;
    e.clear();
}
 
void input(){
    std::cin >> n >> m;
    clear();
    for (int i = 1; i <= m; i++){
        int u, v;
        std::cin >> u >> v;
        list[u].push_back(mk(v, i));
        list[v].push_back(mk(u, i));
        deg[u]++; deg[v]++;
    }
}
 
void findCycle(int v){
    while (!list[v].empty()){
        while (!list[v].empty() && used[list[v].back().nd])
            list[v].pop_back();
        if (list[v].empty())
            break;
        std::pair<int, int> p = list[v].back();
        list[v].pop_back();
        used[p.nd] = true;
        findCycle(p.st);
    }
    e.push_back(v);
}
 
void goCycle(){
    // po prostu szukanie cyklu eulera w tym grafie
    findCycle(1);
    std::cout << 1 << "\n" << e.size() << " ";
    for (auto x: e)
        std::cout << x << " ";
    std::cout << "\n";
}
 
void goNormal(){
    // tworze ten wirtualny wierzcholek i wtedy szukam cyklu
    n++;
    int id = m+1;
    for (int i = 1; i <= n; i++){
        if (deg[i] % 2 == 1){
            list[i].push_back(mk(n, id));
            list[n].push_back(mk(i, id));
            id++;
        }
    }
    findCycle(n);
    int i = 0;
    int j;
    std::vector<std::vector<int> > res;
    std::vector<int> tmp;
    while (i < e.size()-1){
        tmp.clear();
        j = i + 1;
        while (e[j] != n)
            j++;
        for (int k = i+1; k < j; k++)
            tmp.push_back(e[k]);
        res.push_back(tmp);
        i = j;
    }
    std::cout << res.size() << "\n";
    for (auto w: res){
        std::cout << w.size() << " ";
        for (auto x: w)
            std::cout << x << " ";
        std::cout << "\n";
    }
}
 
void solve(){
    input();
    bool found = false;
    for (int i = 1; i <= n; i++)
        if (deg[i] % 2 == 1)
            found = true;
    if (!found)
        goCycle();
    else
        goNormal();
}
 
int main(){
    std::ios_base::sync_with_stdio(0); std::cin.tie(NULL);
    int z;
    std::cin >> z;
    while (z--)
        solve();
}
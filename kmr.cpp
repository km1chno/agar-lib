#include <bits/stdc++.h>
#define mk std::make_pair
#define st first
#define nd second
 
const int MAX_N = 5e5;
int n;
std::string s;
 
int kmr[21][MAX_N+3];
int lcp[MAX_N+3];
int result[MAX_N+3];
 
void build_kmr() {
    std::vector<std::pair<std::pair<int, int>, int> > v;
    int h = 1;
    for (int k = 2; k/2 <= n; k *= 2, h++) {
        v.clear();
        for (int j = 0; j < n; j++) {
            if (j + k/2 < n)
                v.push_back(mk(mk(kmr[h-1][j], kmr[h-1][j + k/2]), j));
            else
                v.push_back(mk(mk(kmr[h-1][j], -1), j));
        }
        std::sort(v.begin(), v.end());
        int id = 0;
        int i = 0;
        int j;
        while (i < n) {
            j = i;
            while (j < n-1 && v[j+1].st == v[i].st)
                j++;
            for (int l = i; l <= j; l++)
                kmr[h][v[l].nd] = id;
            i = j+1;
            id++;
        }
    }
}
 
std::pair<int, int> get_hash(int i, int j) {
    int l = 0;
    while ((1<<(l+1)) <= (j-i+1))
        l++;
    return mk(kmr[l][i], kmr[l][j-(1<<l)+1]);
}
 
void solve() {
    std::cin >> n >> s;
    for (int i = 0; i < n; i++)
        kmr[0][i] = s[i];
    build_kmr();
 
 
    int l = 0;
    while ((1<<l) <= n)
        l++;
 
    std::vector<std::pair<int, int> > v;
    for (int i = 0; i < n; i++)
        v.push_back(mk(kmr[l][i], i));
    std::sort(v.begin(), v.end());
 
    for (int i = 0; i < n-1; i++) {
        int x = v[i].nd;
        int y = v[i+1].nd;
 
        int b = 0;
        int e = std::min(n-x, n-y);
        int mid;
        while (b<e) {
            mid = (b+e+1)/2;
            if (get_hash(x, x+mid-1) == get_hash(y, y+mid-1))
                b = mid;
            else
                e = mid-1;
        }
        lcp[i] = b;
    }
 
    for (int i = 0; i < n; i++) {
        int r = 0;
        if (i < n-1)
            r = std::max(r, lcp[i]);
        if (i > 0)
            r = std::max(r, lcp[i-1]);
        result[v[i].nd] = r;
    }
 
    for (int i = 0; i < n; i++)
        std::cout << result[i] << " ";
    std::cout << "\n";
}
 
int main() {
    std::ios_base::sync_with_stdio(0); std::cin.tie(NULL);
    int z;
    std::cin >> z;
    while (z--)
        solve();
}
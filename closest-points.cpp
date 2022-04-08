#include <bits/stdc++.h>
#define ll long long
#define st first
#define nd second
#define mk std::make_pair
#define debug if(0)
 
struct xy{
    ll x, y;
    xy() {}
    xy(ll X, ll Y) : x(X), y(Y) {}
};
 
int n;
std::vector<xy> v;
const ll inf = LLONG_MAX;
 
void input(){
    std::cin >> n;
    v.clear();
    ll x, y;
    for (int i = 1; i <= n; i++){
        std::cin >> x >> y;
        v.emplace_back(x, y);
    }
}
 
bool cmp1(const xy &A, const xy &B){
    return A.x < B.x;
}
 
bool cmp2(const xy &A, const xy &B){
    return A.y < B.y;
}
 
ll odl(const xy &A, const xy &B){
    return (A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y);
}
 
ll go(int L, int R){
    if (L == R)
        return inf;
    int mid = (L+R)/2;
    ll d = go(L, mid);
    d = std::min(d, go(mid+1, R));
    ll dd = ceil(sqrtl(d));
    ll res = inf;
    ll line = v[mid].x;
    std::vector<xy> left, right;
    for (int i = L; i <= mid; i++){
        if (line - v[i].x <= dd)
            left.push_back(v[i]);
    }
    for (int i = mid+1; i <= R; i++){
        if (v[i].x - line <= dd)
            right.push_back(v[i]);
    }
    std::sort(left.begin(), left.end(), cmp2);
    std::sort(right.begin(), right.end(), cmp2);
    int it, it1; it = it1 = 0;
    for (auto p: left){
        while (it < right.size() && p.y - right[it].y > dd)
            it++;
        it1 = it;
        while (it1 < right.size() && right[it1].y - p.y <= dd){
            res = std::min(res, odl(p, right[it1]));
            it1++;
        }
    }
    return std::min(d, res);
}
 
void solve(){
    input();
    std::sort(v.begin(), v.end(), cmp1);
    ll res = go(0, v.size()-1);
    std::cout << res << "\n";
}
 
int main(){
    std::ios_base::sync_with_stdio(0); std::cin.tie(NULL);
    int z;
    std::cin >> z;
    while (z--)
        solve();
}
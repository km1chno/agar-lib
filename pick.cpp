#include <bits/stdc++.h>
#define ll long long
 
struct xy{
    ll x, y;
    xy(ll X, ll Y) : x(X), y(Y) {}
};
 
std::vector<xy> v;
int n;
 
void input(){
    std::cin >> n;
    v.clear();
    ll x, y;
    for (int i = 1; i <= n; i++){
        std::cin >> x >> y;
        v.emplace_back(x, y);
    }
}
 
ll abss(ll x){
    if (x < 0)
        return x * (ll)(-1);
    return x;
}
 
ll gcd(ll x, ll y){
    if (y == 0)
        return x;
    return gcd(y, x%y);
}
 
ll det(xy A, xy B){
    // 0  0  1  0  0
    // Ax Ay 1  Ax Ay
    // Bx By 1  Bx By
    return A.x*B.y - A.y*B.x;
}
 
void solve(){
    input();
    // wynik = Pole - 1/2B + 1
    // 2*wynik = 2*Pole - B + 2
    ll P = 0;
    for (int i = 0; i < v.size()-1; i++)
        P += det(v[i], v[i+1]);
    P += det(v.back(), v[0]);
    P = abss(P);
    ll B = 0;
    for (int i = 0; i < v.size()-1; i++)
        B += gcd( abss(v[i].x - v[i+1].x), abss(v[i].y - v[i+1].y));
    B += gcd( abss(v.back().x - v[0].x), abss(v.back().y - v[0].y));
    ll res = P - B + 2;
    std::cout << res/2 << "\n";
}
 
int main(){
    std::ios_base::sync_with_stdio(0); std::cin.tie(NULL);
    int z;
    std::cin >> z;
    while (z--)
        solve();
}
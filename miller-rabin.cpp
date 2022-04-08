#include <bits/stdc++.h>
#define ll long long
#define int128 __int128_t
 
int128 pot(int128 a, int128 p, int128 mod){
    if (p == 0)
        return 1;
    else if (p % 2 == 0){
        int128 tmp = pot(a, p/2, mod);
        return (tmp * tmp)%mod;
    }
    return (pot(a, p-1, mod) * a)%mod;
}
 
bool witness(int128 a, int128 n){
    int128 _n = n-1;
    while (_n % 2 == 0)
        _n /= 2;
    int128 b = pot(a, _n, n);
    if (b == 1)
        return false;
    if (b == n-1)
        return false;
    while (_n < n-1){
        b = (b * b) % n;
        _n *= 2;
        if (b == n-1)
            return false;
    }
    return true;
}
 
void solve(){
    ll n; std::cin >> n;
    for (int i = 1; i <= 20; i++){
        ll a = rand()%(n-1)+1;
        if (witness(a, n)){
            std::cout << "NIE\n";
            return;
        }
    }
    std::cout << "TAK\n";
}
 
int main(){
    std::ios_base::sync_with_stdio(0); std::cin.tie(NULL);
    int z;
    std::cin >> z;
    while (z--)
        solve();
}
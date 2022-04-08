#include <bits/stdc++.h>
 
struct Tuple{
    int d, x, y;
    void set(int d, int x, int y){
        this->d = d; this->x = x; this->y = y;
    }
};
 
Tuple nwd(int a, int b){
    Tuple res;
    if (b == 0){
        res.set(a, 1, 0);
        return res;
    }
    res = nwd(b, a%b);
    res.set(res.d, res.y, res.x - (res.y * (a/b)));
    return res;
}
 
void solve(){
    int a, n;
    std::cin >> a >> n;
    Tuple res = nwd(a, n);
    if (res.d != 1)
        std::cout << "NIE ISTNIEJE\n";
    else
        std::cout << (res.x + n) % n << "\n";
}
 
int main(){
    std::ios_base::sync_with_stdio(0); std::cin.tie(NULL);
    int z;
    std::cin >> z;
    while (z--)
        solve();
}
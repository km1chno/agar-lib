#include <bits/stdc++.h>
#define ld long double
 
struct XY{
    ld x, y;
    XY(){}
    XY(ld a, ld b) : x(a), y(b) {}
};
 
const ld EPS = 1e-9;
const int MAX_N = 2e5;
int n;
ld R;
std::vector<XY> v;
std::vector<XY> hull;
 
void input(){
    std::cin >> n >> R;
    ld x, y;
    v.clear();
    hull.clear();
    for (int i = 1; i <= n; i++){
        std::cin >> x >> y;
        v.emplace_back(x, y);
    }
}
 
int root;
XY P;
 
ld dist(XY A, XY B){
    return sqrt((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y));
}
 
ld det(XY A, XY B, XY C){
    return (A.x*B.y + A.y*C.x + B.x*C.y) - (A.y*B.x + A.x*C.y + B.y*C.x);
}
 
bool cmp1(const XY &p1, const XY &p2){
    ld D = det(P, p1, p2);
    if (D > 0+EPS)
        return true;
    else if (D > 0-EPS)
        return dist(P, p1) <= dist(P, p2);
    return false;
}
 
void graham(){
    hull.push_back(P);
    if (!v.empty())
        hull.push_back(v[0]);
    for (int i = 1; i < v.size(); i++){
        while (v.size() >= 2 && det(hull[hull.size()-2], hull[hull.size()-1], v[i]) < 0+EPS)
            hull.pop_back();
        hull.push_back(v[i]);
    }
}
 
void solve(){
    input();
    root = 0;
    for (int i = 1; i < n; i++)
        if (v[i].y < v[root].y || (v[i].y == v[root].y && v[i].x < v[root].x))
            root = i;
    P = v[root];
    v.erase(v.begin()+root);
    std::stable_sort(v.begin(), v.end(), cmp1);
    graham();
    ld res = 0;
    for (int i = 0; i < hull.size()-1; i++)
        res += dist(hull[i], hull[i+1]);
    res += dist(hull.back(), hull[0]);
    res += 2*M_PI*R;
    std::cout << std::setprecision(2) << std::fixed << res << "\n";
}
 
int main(){
    std::ios_base::sync_with_stdio(0); std::cin.tie(NULL);
    int z;
    std::cin >> z;
    while (z--)
        solve();
}
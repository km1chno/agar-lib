#include <bits/stdc++.h>
#define ld long double
 
const int MAX_N = 2e5;
const ld eps = 1e-10;
 
struct xy{
    ld x, y;
 
    xy(){ x = y = 0; }
    xy(ld a, ld b) : x(a), y(b) {}
};
 
struct Line{
    ld A, B, C;
 
    Line(){}
    Line(ld a, ld b, ld c) : A(a), B(b), C(c) {}
 
    xy get_intersection(Line k){
        ld W = A*k.B - k.A*B;
        ld Wx = (-C)*k.B - (-k.C)*B;
        ld Wy = A*(-k.C) - k.A*(-C);
        xy M(Wx/W, Wy/W);
        return M;
    }
};
 
struct Segment{
    xy A, B;
 
    Segment(){}
    Segment(xy X, xy Y) : A(X), B(Y) {}
 
    xy get_midpoint(){
        xy C((A.x+B.x)/2, (A.y+B.y)/2);
        return C;
    }
 
    Line get_line(){
        Line L(A.y - B.y, B.x - A.x, A.x*B.y - B.x*A.y);
        return L;
    }
 
    Line get_bisector(){ 
        xy M = get_midpoint(); 
        Line K = get_line(); 
        Line L(K.B, -K.A, -1);
        L.C = -(L.A * M.x + L.B * M.y);
        return L;
    }
};
 
ld distance(xy A, xy B){
    return sqrt((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y));
}
 
struct Circle {
    int cnt; /* how many points define the circle, if cnt==2, then A--B is the diameter */
    xy A, B, C;
 
    Circle(){}
    Circle(xy X) : A(X), cnt(1) {}
    Circle(xy X, xy Y) : A(X), B(Y), cnt(2) {}
    Circle(xy X, xy Y, xy Z) : A(X), B(Y), C(Z), cnt(3) {}
 
    xy get_center() { 
        if (cnt == 2){
            Segment AB(A, B);
            return AB.get_midpoint();
        }
        Segment AB(A, B);
        Segment AC(A, C);
        Line K = AB.get_bisector();
        Line L = AC.get_bisector(); 
        xy center = K.get_intersection(L); 
        return center;
    }
 
    ld get_radius(){
        xy center = get_center(); 
        return distance(center, A);
    }
 
    bool is_inside(xy X){
        xy center = get_center();
        ld r = get_radius();
        return distance(center, X) <= r + eps;
    }
};
 
int n;
std::vector<xy> v;
 
void input(){
    std::cin >> n;
    v.clear();
    ld x, y;
    for (int i = 1; i <= n; i++){
        std::cin >> x >> y;
        v.emplace_back(x, y);
    }
}
 
Circle min_disk3(int i, int j, int h){
    Circle CC(v[i], v[j], v[h]);
    return CC;
}
 
Circle min_disk2(int i, int j){
    Circle C(v[i], v[j]);
    for (int h = 0; h < j; h++)
        if (!C.is_inside(v[h]))
            C = min_disk3(i, j, h);
    return C;
}
 
Circle min_disk1(int i){
    Circle C(v[i], v[0]);
    for (int j = 1; j < i; j++)
        if (!C.is_inside(v[j]))
            C = min_disk2(i, j);
    return C;
}
 
void solve(){
    input();
    std::random_shuffle(v.begin(), v.end());
    Circle C(v[0], v[1]);
    for (int i = 2; i < n; i++){
        if (!C.is_inside(v[i])){
            C = min_disk1(i);
        }
    }
    std::cout << std::setprecision(12) << std::fixed << C.get_radius() << "\n";
}
 
int main(){
    srand(time(NULL));
    int z;
    std::cin >> z;
    while (z--)
        solve();
}
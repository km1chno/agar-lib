#include <bits/stdc++.h>
#define ll long long

struct xy {
    ll x, y;

    xy(ll X, ll Y) : x(X), y(Y) {}
    xy() : x(0), y(0) {}
};

ll dist(const xy &a, const xy &b) {
    ll dx = a.x - b.x;
    ll dy = a.y - b.y;
    return dx*dx + dy*dy;
}

/* det((a,b), (a,c)) */
/* det > 0 iff c is to the right of b */
ll det(const xy &a, const xy &b, const xy &c) {
    return (b.y-a.y)*(c.x-a.x) - (c.y-a.y)*(b.x-a.x);
}

xy P;

bool polar_cmp(const xy &a, const xy &b) {
    ll d = det(P, a, b);
    if (d < 0)
        return true;
    else if (d == 0) 
        return dist(P, a) < dist(P, b);
    return false;
}

std::vector<xy> graham(std::vector<xy> &v) {
    P = v[0];
    int root = 0;
    for (int i = 1; i < v.size(); i++)
        if (v[i].y < P.y || (v[i].y == P.y && v[i].x < P.x)) {
            root = i;
            P = v[root];
        }
    v.erase(v.begin()+root);
    std::sort(v.begin(), v.end(), polar_cmp);
    std::vector<xy> hull;
    hull.push_back(P);
    hull.push_back(v[0]);

    for (int i = 1; i < v.size(); i++) {
        while (hull.size() >= 2 && det(hull[hull.size()-2], hull.back(), v[i]) >= 0)
            hull.pop_back();
        hull.push_back(v[i]);
    }
    return hull;
}
#include <bits/stdc++.h>
#define ll long long
#define st first 
#define nd second

/* UTILS */
__int128_t fast_pow(__int128_t a, __int128_t b, __int128_t P) {
    if (b == 0)
        return 1;
    else if (b % 2 == 0) {
        __int128_t tmp = fast_pow(a, b/2, P);
        return tmp * tmp % P;
    }
    return fast_pow(a, b-1, P) * a % P;
}

__int128_t modulo_inv(__int128_t a, __int128_t p) {
    return fast_pow(a, p-2, p);
}

/* MILLER-RABIN */
bool witness(__int128_t a, __int128_t n) {
    __int128_t _n = n-1;
    while (_n % 2 == 0)
        _n /= 2;
    __int128_t b = fast_pow(a, _n, n);
    if (b == 1 || b == n-1)
        return false;
    while (_n < n-1) {
        b = b * b % n;
        _n *= 2;
        if (b == n-1)
            return false;
    }
    return true;
}
 
bool is_prime(ll n) {
    for (int i = 1; i <= 20; i++){
        ll a = rand()%(n-1)+1;
        if (witness(a, n))
            return false;
    }
    return true;
}

/* DISCRETE LOGARITHM */
/* returns smallest x such that a^x = b (mod p) or -1 if doesnt exist */
ll discrete_log(ll a, ll b, ll p) {
    ll tmp = sqrt(p);
    ll root = std::max((ll)(10), tmp);
    root = std::min(root, p);
    std::vector<std::pair<ll, ll> > A, B;
    for (int i = 0; i <= root; i++){
        A.push_back({fast_pow(a, i*root, p), i});
        B.push_back({(b * modulo_inv(fast_pow(a, i, p), p)) % p, i});
    }
    std::sort(A.begin(), A.end());
    std::sort(B.begin(), B.end());
    int it = 0;
    ll res = -1;
    for (int i = 0; i < A.size(); i++){
        while (it < B.size()-1 && B[it].st < A[i].st)
            it++;
        if (B[it].st == A[i].st){
            if (res == -1 || A[i].nd * root + B[it].nd < res){
                res = A[i].nd * root + B[it].nd;
            }
        }
    }
    return res;
}

/* EXTENDED EUCLIDEAN ALG */ 
struct Tuple {
    int d, x, y;
    void set(int d, int x, int y){
        this->d = d; this->x = x; this->y = y;
    }
};
 
/* returns d, x, y such that d = gcd(a, b) and ax + by = d */
Tuple nwd(int a, int b) {
    Tuple res;
    if (b == 0){
        res.set(a, 1, 0);
        return res;
    }
    res = nwd(b, a%b);
    res.set(res.d, res.y, res.x - (res.y * (a/b)));
    return res;
}
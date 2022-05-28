#include <bits/stdc++.h>
#define ll long long
 
__int128_t fast_pow(__int128_t a, __int128_t b, __int128_t P) {
    if (b == 0)
        return 1;
    else if (b % 2 == 0) {
        __int128_t tmp = fast_pow(a, b/2, P);
        return tmp * tmp % P;
    }
    return fast_pow(a, b-1, P) * a % P;
}
 
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

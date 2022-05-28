#include <bits/stdc++.h>
#define ll long long
    
ll MOD = 1e9+7;
ll fast_pow(ll a, ll b) {
    if (b == 0)
        return 1;
    if (b % 2 == 0) {
        ll temp = fast_pow(a, b/2);
        return temp * temp % MOD;
    }
    return a * fast_pow(a, b-1) % MOD;
}

ll lagrangeInterpolation(
    std::vector<ll> &x,
    std::vector<ll> &y, 
    ll p) 
{
    ll res = 0;
    for (int i = 0; i < x.size(); i++) {
        ll L = y[i];
        ll M = 1;
        for (int j = 0; j < x.size(); j++) {
            if (j == i) continue;
            L = L * (p-x[j]+MOD) % MOD;
            M = M * (x[i]-x[j]+MOD) % MOD;
        }
        L = L * fast_pow(M, MOD-2);
        res = (res + L) % MOD;
    }
    return res;
}
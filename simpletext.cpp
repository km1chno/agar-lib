#include <bits/stdc++.h>

/* pref pref */
void calc_pp(std::string &A, std::vector<int> &pp) {
    pp[1] = 0;
    int t = 1;
    for (int i = 2; i <= A.length()-1; i++) {
        if (i <= t+pp[t]-1)
            pp[i] = std::min(t+pp[t]-i, pp[i-t+1]);
        while (A[pp[i]+1] == A[i+pp[i]])
            pp[i]++;
        if (i + pp[i] - 1 >= t + pp[t] -1)
            t = i;
    }
}

/* pref suf */
void calc_ps(std::string &A, std::vector<int> &ps) {
    int n = A.length();
    ps[0] = ps[1] = 0;
    for (int i = 2; i <= n; i++) {
        ps[i] = 0;
        int p = ps[i-1];
        while (p > 0 && A[i] != A[p+1])
            p = ps[p];
        if (A[i] == A[p+1])
            ps[i] = p+1;
    }
}   

/* manacher */
void calc_manacher(std::string &s, std::vector<int> &pp) {
    int n = s.length();
    pp[1] = 0;
    int i = 1;
    int t = 0;
    while (i <= n){
        while (s[i-t-1] == s[i+t+1])
            t++;
        pp[i] = t;
        int k = 1;
        while (k <= t && pp[i]-k != pp[i-k]){
            pp[i+k] = std::min(pp[i]-k, pp[i-k]);
            k++;
        }
        t -= k;
        t = std::max(0, t);
        i += k;
    }
}
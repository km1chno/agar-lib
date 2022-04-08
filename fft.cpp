#include <bits/stdc++.h>

#define K long long

/* P = 2^k * c + 1, where c is odd
 * then we set N = 2^k 
 * we first find generator g over field Z_P with hit and try method
 * then calculate g^c, that's the result 
 *
 * if we want smaller N = 2^q for q < k,
 * then multiply the result times g^{2^{k-q}}
 * 
 * the function below returns g^c, 
 */

K P, g, N;

K fast_pow(K a, K b, K P) {
    if (b == 0) return 1;
    if (b % 2 == 0) { K tmp = fast_pow(a, b/2, P); return tmp * tmp % P; }
    return a * fast_pow(a, b-1, P) % P; 
}

bool is_gen(K g, K P) {
    K q = g;
    for (K i = 1; i < P-1; i++) {
        if (g == 1)
            return false;
        g = g * q % P; 
    }
    return true;
}

K find_gen(K P) {
    // copied from https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(2, P-1);
 
    K g = 1;
    while (1) {
        g = distrib(gen);
        std::cout << "Checking " << g << "\n";
        fflush(stdout);
        if (is_gen(g, P)) {
            K Q = P-1; while (Q % 2 == 0) Q /= 2;
            std::cout << "Q = " << Q << "\n";
            return fast_pow(g, Q, P);
        }
    }
}

K find_root(K M) {
    if (M > N) return 1;
    return fast_pow(g, (1<<(N-M)), P);
}

void ntt(std::vector<K> &x, int d) {
    std::vector<K> e;
    int n = x.size(); e.resize(n+1);
    int pow = 0;
    while ((1<<pow) < n) pow++;
    e[0] = 1; e[1] = find_root(pow);
    if (d == -1) e[1] = fast_pow(e[1], P-2, P);
    for (int i = 2; i < n; i++) e[i] = e[i-1] * e[1] % P; 
    for (int i = 0; i < n; i++) {
        int j = 0; 
        for (int k = 1; k < n; k <<= 1, j <<= 1) if (k & i) j++;
        j >>= 1; if (i < j) std::swap(x[i], x[j]);
    }
    int k=0;
    while ((1 << k) < n) k++;
    for(int s = 1; s < n; s <<= 1){
        --k;
        for(int i = 0; i < n; i += 2*s) for (int j = 0; j < s; j++) {
            K u = x[i+j], v = x[i+j+s] * e[j<<k] % P; 
            x[i+j] = u + v - (u+v >= P ? P : 0);
            x[i+j+s] = u - v + (u-v < 0 ? P : 0);
        }
    }
    if (d == -1) {
        K n_inv = fast_pow(n, P-2, P);
        for (int i = 0; i < n; i++) x[i] = x[i] * n_inv % P;
    }
}

std::vector<K> mul(std::vector<K> A, std::vector<K> B) {
    K pow = 1; int l = std::max(A.size(), B.size());
    while ((1<<pow) < l) ++pow;
    ++pow;
    A.resize(1<<pow); B.resize(1<<pow);
    ntt(A, 1); ntt(B, 1);
    for (int i = 0; i < A.size(); i++) A[i] = A[i] * B[i] % P;
    ntt(A, -1);
    while (A.size() > 1 && A.back() == 0) A.pop_back();
    return A;
}

std::vector<K> inv(std::vector<K> A) {
    int pow = 0;
    while ((1<<pow) < A.size()) 
        ++pow;
    A.resize((1<<pow)-1);
    std::vector<K> R(1, fast_pow(A[0], P-2, P));
    for (int k = 1; k <= pow; k++) {
        std::vector<K> B(A.begin(), A.begin() + (1<<k));
        R.resize(1<<(k+1)); B.resize(1<<(k+1));
        K w = find_root(k+1);
        ntt(R, 1); ntt(B, 1);
        for (int i = 0; i < (1<<(k+1)); i++) 
            R[i] = (2 * R[i] % P - (R[i] * R[i] % P * B[i] % P)) % P;
        for (int i = 0; i < (1<<(k+1)); i++)
            R[i] = (R[i] + P) % P;
        ntt(R, -1);
        R.resize(1<<k);
    }
    return R;
}


int main() {
    srand(time(NULL));
    K P; std::cin >> P;
    /* 
     * P = 998244353;
     * g = 879587319; (find_gen(P))
     * N = 23;
     */
}
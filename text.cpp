#include <bits/stdc++.h>
using namespace std;

typedef long long lld;
typedef __int128_t int128;

/** StringHash(s: string) offers equality checks for substrings in O(1) and
 * less/greater checks in O(log n). For queries, assume string is indexed 1..n.
 */
struct StringHash {
  const lld P = 1e18 + 9;
  const lld A = 27;

  int n;
  string s;
  vector<lld> p;
  vector<lld> B;

  // O(n)
  StringHash(string _s) : s(_s) {
    n = s.length();
    p.assign(n + 3, 0);
    B.assign(n + 3, 1);
    for (int i = 1; i <= n; i++)
      B[i] = ((int128)B[i - 1] * A) % P;
    for (int i = n; i > 0; i--)
      p[i] = ((int128)p[i + 1] * A + s[i - 1]) % P;
  }

  // O(1)
  lld hash(int l, int r) {
    lld h = p[l] - ((int128)p[r + 1] * B[r - l + 1] % P);
    if (h < 0)
      h += P;
    return h;
  }

  // true iff s[l1..r1] == s[l2..r2]
  // O(1)
  bool eq(int l1, int r1, int l2, int r2) {
    return hash(l1, r1) == hash(l2, r2);
  }

  // returns lcp(s[l1..r1], s[l2..r2])
  // O(log n)
  int lcp(int l1, int r1, int l2, int r2) {
    int b = 0;
    int e = min(r1 - l1, r2 - l2);
    int mid;

    while (b < e) {
      mid = (b + e + 1) / 2;
      if (eq(l1, l1 + mid - 1, l2, l2 + mid - 1))
        b = mid;
      else
        e = mid - 1;
    }

    return b;
  }

  // true iff s[l1..r1] < s[l2..r2]
  // O(log n)
  bool less(int l1, int r1, int l2, int r2) {
    if (eq(l1, r1, l2, r2))
      return false;
    int l = lcp(l1, r1, l2, r2);
    if (l == (r1 - l1 + 1))
      return true;
    if (l == (r2 - l2 + 1))
      return false;
    return s[l1 + l - 1] < s[l2 + l - 1];
  }

  // true iff s[l1..r1] > s[l2..r2]
  // O(log n)
  bool greater(int l1, int r1, int l2, int r2) {
    return !eq(l1, r1, l2, r2) && !less(l1, r1, l2, r2);
  }
};

// Calculates pref-pref array indexed 0..n-1 in O(n).
vector<int> calc_pp(string &A) {
  int n = A.length();
  vector<int> pp(n, 0);
  int t = 1;
  for (int i = 1; i < n; i++) {
    if (i <= t + pp[t] - 1)
      pp[i] = min(t + pp[t] - i, pp[i - t]);
    while (i + pp[i] < n && A[pp[i]] == A[i + pp[i]])
      pp[i]++;
    if (i + pp[i] >= t + pp[t])
      t = i;
  }
  return pp;
}

// Calculates pref-suf array indexed 0..n-1 in O(n).
vector<int> calc_ps(string &A) {
  int n = A.length();
  vector<int> ps(n + 1, 0);
  int pref = 0;
  for (int i = 2; i <= n; i++) {
    while (pref > 0 && A[i] != A[pref + 1])
      pref = ps[pref];
    if (A[i] == A[pref + 1])
      pref++;
    ps[i] = pref;
  }
  return ps;
}

// Calculates palindromic radii array indexed 0..n-1 in O(n).
vector<int> calc_manacher(string &s) {
  int n = s.length();
  vector<int> pp(n, 0);
  int j = 0;
  for (int i = 1; i < n; i++) {
    if (i <= j + pp[j] - 1)
      pp[i] = min(pp[2 * j - i], j + pp[j] - 1 - i);
    while ((i - pp[i] - 1) >= 0 && (i + pp[i] + 1) < n &&
           s[i - pp[i] - 1] == s[i + pp[i] + 1])
      pp[i]++;
    if (i + pp[i] > j + pp[j])
      j = i;
  }
  return pp;
}

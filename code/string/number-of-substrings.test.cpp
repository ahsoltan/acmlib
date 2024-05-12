#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "SuffixArray.h"

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  cin >> s;
  int n = ssize(s);
  auto p = suffix_array(s);
  auto lcp = build_lcp(s, p);
  ll ans = 1ll * n * (n + 1) / 2;
  for (int i = 0; i < n - 1; i++) {
    ans -= lcp[i];
  }
  cout << ans << '\n';
}
 

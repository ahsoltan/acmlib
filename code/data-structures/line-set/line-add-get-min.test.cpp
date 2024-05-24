#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "main.hpp"

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  line_set s;
  for (int i = 0; i < n; i++) {
    ll a, b;
    cin >> a >> b;
    s.add(-a, -b);
  }
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      ll a, b;
      cin >> a >> b;
      s.add(-a, -b);
    } else {
      ll x;
      cin >> x;
      cout << -s.get(x) << '\n';
    }
  }
}


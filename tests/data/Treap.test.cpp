#define PROBLEM "https://judge.yosupo.jp/problem/range_reverse_range_sum"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "content/data/Treap.h"

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  node* tt = 0;
  vector<node> t(n);
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    t[i] = node(a);
    tt = merge(tt, &t[i]);
  }
  while (q--) {
    int t, l, r;
    cin >> t >> l >> r;
    auto [x, yz] = split(tt, l);
    auto [y, z] = split(yz, r - l);
    if (t == 1) cout << (y ? y->sum : 0) << '\n';
    else if (y) y->rev ^= 1;
    tt = merge(x, merge(y, z));
  }
}

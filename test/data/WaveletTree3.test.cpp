#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "content/data/WaveletTree.h"

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  if (n == 0) {
    while (q--) cout << "0\n";
    return 0;
  }
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  auto b = a;
  sort(b.begin(), b.end());
  node t(a.begin(), a.end(), b.begin());
  while (q--) {
    int l, r, k;
    cin >> l >> r >> k;
    cout << t.count(l, r, k + 1) - t.count(l, r, k) << '\n';
  }
}
 

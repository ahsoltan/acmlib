#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "content/math/NTT.h"

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<mint> a(n), b(m);
  for (int i = 0; i < n; i++) cin >> a[i].x;
  for (int i = 0; i < m; i++) cin >> b[i].x;
  auto c = conv(move(a), move(b));
  for (int i = 0; i < n + m - 1; i++) {
    cout << c[i].x << " \n"[i == n + m - 2];
  }
}

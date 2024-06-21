#define PROBLEM "https://judge.yosupo.jp/problem/factorize"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "content/math/PollardRho.h"

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int q;
  cin >> q;
  while (q--) {
    ull n;
    cin >> n;
    map<ull, int> cnt;
    factor(n, cnt);
    vector<ull> f;
    for (auto [x, y] : cnt) {
      f.insert(f.end(), y, x);
    }
    cout << ssize(f);
    for (ull x : f) cout << ' ' << x;
    cout << '\n';
  }
}

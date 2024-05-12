#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "Matching.h"

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int l, r, m;
  cin >> l >> r >> m;
  matching g(l, r);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    g.add_edge(u, v);
  }
  cout << g.match() << '\n';
  for (int i = 0; i < l; i++) {
    if (g.pb[i] != -1) {
      cout << i << ' ' << g.pb[i] << '\n';
    }
  }
}
 

#define PROBLEM "https://judge.yosupo.jp/problem/assignment"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "content/graph/MCMF.h"

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  MCMF g(2 * n + 2);
  g.pi.assign(g.n, INF);
  g.pi[0] = 0;
  for (int i = 0; i < n; i++) {
    g.pi[2 + i] = 0;
    g.add_edge(0, 2 + i, 1, 0);
    g.add_edge(2 + n + i, 1, 1, 0);
    for (int j = 0; j < n; j++) {
      int a;
      cin >> a;
      g.add_edge(2 + i, 2 + n + j, 1, a);
      g.pi[2 + n + j] = min(g.pi[2 + n + j], (ll)a);
      g.pi[1] = min(g.pi[1], (ll)a);
    }
  }
  cout << g.flow(0, 1, n).second << '\n';
  for (int i = 0; i < n; i++) {
    for (auto& e : g.adj[2 + i]) {
      if (!e.cap && e.to >= 2 + n) {
        cout << e.to - (2 + n) << " \n"[i == n - 1];
        break;
      }
    }
  }
}

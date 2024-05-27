#define PROBLEM "https://judge.yosupo.jp/problem/scc"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "graph/SCC.h"

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  SCC g(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    g.add_edge(u, v);
  }
  g.build();
  vector<vector<int>> gr(g.cnt);
  for (int i = 0; i < n; i++) {
    gr[g.p[i]].push_back(i);
  }
  cout << g.cnt << '\n';
  for (int i = 0; i < g.cnt; i++) {
    cout << ssize(gr[i]);
    for (int j : gr[i]) cout << ' ' << j;
    cout << '\n';
  }
}
 

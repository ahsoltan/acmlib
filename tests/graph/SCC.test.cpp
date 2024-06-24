#define PROBLEM "https://judge.yosupo.jp/problem/scc"
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) int((x).size())
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#ifdef LOCAL
auto& operator<<(auto&, pair<auto, auto>);
auto operator<<(auto& o, auto x) -> decltype(x.end(), o) {
  o << '{';
  for (int i = 0; auto y : x) o << ", " + !i++ * 2 << y;
  return o << '}';
}
auto& operator<<(auto& o, pair<auto, auto> x) {
  return o << '(' << x.first << ", " << x.second << ')';
}
void __print(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "[" #x "]:", __print(x)
#else
#define debug(...) 2137
#endif

#include "content/graph/SCC.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  SCC scc(n);
  while (m--) {
    int u, v;
    cin >> u >> v;
    scc.add_edge(u, v);
  }
  scc.build();
  vector<vi> c(scc.cnt);
  rep(i, 0, n) c[scc.p[i]].push_back(i);
  cout << scc.cnt << '\n';
  rep(i, 0, scc.cnt) {
    cout << sz(c[i]);
    for (int u : c[i]) cout << ' ' << u;
    cout << '\n';
  }
}

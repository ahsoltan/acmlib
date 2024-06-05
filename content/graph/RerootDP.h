/**
 * Opis: Oblicza DP z każdego korzenia.
 * Czas: O(n \log n)
 */
#pragma once

template<typename T>
vector<T> reroot(const auto& adj) {
  int n = ssize(adj);
  vector<int> q(n), p(n, -1);
  for (int i = 0, j = 1; i < n; i++) {
    int u = q[i];
    for (int v : adj[u]) if (v != p[u]) p[v] = u, q[j++] = v;
  }
  vector<T> dp(n), ans(n), rdp(n);
  for (int i = n - 1; i >= 0; i--) {
    int u = q[i], pi = -1;
    dp[u].init(u);
    for (int j = 0; j < ssize(adj[u]); j++) {
      if (adj[u][j] != p[u]) dp[u].merge(u, j, dp[adj[u][j]]);
      else pi = j;
    }
    ans[u] = dp[u];
    dp[u].push(u, pi);
  }
  for (int u : q) {
    auto sum = [&](T& s, int l, int r) {
      for (int i = l; i < r; i++) {
        int v = adj[u][i];
        s.merge(u, i, v != p[u] ? dp[v] : rdp[u]);
      }
    };
    auto rec = [&](auto self, int l, int r, const T& s) {
      if (l + 1 == r) {
        if (adj[u][l] != p[u]) rdp[adj[u][l]] = s;
        return;
      }
      int m = (l + r) / 2;
      T ss = s; sum(ss, l, m); self(self, m, r, ss);
      ss = s; sum(ss, m, r); self(self, l, m, ss);
    };
    T s; s.init(u);
    if (n > 1) rec(rec, 0, ssize(adj[u]), s);
    for (int i = 0; i < ssize(adj[u]); i++) {
      if (adj[u][i] != p[u]) rdp[adj[u][i]].push(u, i);
      else ans[u].merge(u, i, rdp[u]);
    }
    ans[u].push(u, -1);
  }
  return ans;
}
struct DP {
  void init(int u) {}
  void merge(int u, int i, const DP& s) {}
  void push(int u, int i) {}
};

/**
 * Opis: Znajduje SCC w kolejności topologicznej.
 * Czas: O(n + m)
 */
#pragma once

struct SCC {
  int n, t = 0, cnt = 0;
  vector<vi> adj;
  vi val, p, st;
  SCC(int _n) : n(_n), adj(n), val(n), p(n, -1) {}
  void add_edge(int u, int v) { adj[u].push_back(v); }
  int dfs(int u) {
    int low = val[u] = ++t; st.push_back(u);
    for (int v : adj[u]) if (p[v] == -1)
      low = min(low, val[v] ?: dfs(v));
    if (low == val[u]) {
      for (int x = -1; x != u;)
        p[x = st.back()] = cnt, st.pop_back();
      cnt++;
    }
    return low;
  }
  void build() {
    rep(i, 0, n) if (!val[i]) dfs(i);
    rep(i, 0, n) p[i] = cnt - 1 - p[i];
  }
};

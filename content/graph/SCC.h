/**
 * Opis: Znajduje silnie spójne składowe.
 * `cnt` -- ilość spójnych,
 * `p[i]` -- numer spójnej w kolejności topologicznej.
 * Czas: O(n + m)
 */
#pragma once

struct SCC {
  int n, t = 0, cnt = 0;
  vector<vector<int>> adj;
  vector<int> val, p, st;
  SCC(int _n) : n(_n), adj(n), val(n), p(n, -1) {}
  void add_edge(int u, int v) { adj[u].push_back(v); }
  int dfs(int u) {
    int low = val[u] = ++t; st.push_back(u);
    for (int v : adj[u]) if (p[v] == -1) {
      low = min(low, val[v] ?: dfs(v));
    }
    if (low == val[u]) {
      for (int x = -1; x != u;) {
        p[x = st.back()] = cnt, st.pop_back();
      }
      cnt++;
    }
    return low;
  }
  void build() {
    st.reserve(n);  
    for (int i = 0; i < n; i++) if (p[i] == -1) dfs(i);
    for (int i = 0; i < n; i++) p[i] = cnt - 1 - p[i];
  }
};

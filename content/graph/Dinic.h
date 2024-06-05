/**
 * Opis: Znajduje największy przepływ.
 * Na niektórych grafach może być szybszy bez skalowania.
 * Czas: O(nm \log U)
 */
#pragma once

struct dinic {
  struct edge {
    int to, rev;
    ll cap;
  };
  int n;
  vector<vector<edge>> adj;
  vector<int> q, lvl, it;
  dinic(int _n) {
    n = _n;
    adj.resize(n);
    q.resize(n);
  }
  void add_edge(int u, int v, ll cap, ll rcap = 0) {
    int i = ssize(adj[u]), j = ssize(adj[v]);
    adj[u].push_back({v, j + (u == v), cap});
    adj[v].push_back({u, i, rcap});
  }
  ll dfs(int u, int t, ll cap) {
    if (u == t || !cap) return cap;
    for (int& i = it[u]; i < ssize(adj[u]); i++) {
      edge& e = adj[u][i];
      if (lvl[e.to] == lvl[u] + 1) {
        if (ll d = dfs(e.to, t, min(cap, e.cap))) {
          e.cap -= d, adj[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }
  ll flow(int s, int t, ll cap) {
    ll f = 0; q[0] = s;
    for (int b = 62; b >= 0; b--) {
      do {
        lvl.assign(n, 0); it.assign(n, 0);
        int l = 0, r = lvl[s] = 1;
        while (l < r && !lvl[t]) {
          int u = q[l++];
          for (edge e : adj[u]) {
            if (!lvl[e.to] && e.cap >> b) {
              lvl[e.to] = lvl[u] + 1, q[r++] = e.to;
            }
          }
        }
        while (ll d = dfs(s, t, cap)) f += d, cap -= d;
      } while (lvl[t]);
    }
    return f;
  }
};

/**
 * Opis: Dinic ze skalowaniem.
 * Należy ustawić zakres `it` w `flow` zgodnie z $U$.
 * Czas: O(nm \log U)
 */
#pragma once

struct dinic {
  struct edge {
    int to, rev;
    ll cap;
  };
  vi lvl, ptr, q;
  vector<vector<edge>> adj;
  dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
  void add_edge(int u, int v, ll cap, ll rcap = 0) {
    int i = sz(adj[u]), j = sz(adj[v]);
    adj[u].push_back({v, j + (u == v), cap});
    adj[v].push_back({u, i, rcap});
  }
  ll dfs(int v, int t, ll f) {
    if (v == t || !f) return f;
    for (int& i = ptr[v]; i < sz(adj[v]); i++) {
      edge& e = adj[v][i];
      if (lvl[e.to] == lvl[v] + 1)
        if (ll p = dfs(e.to, t, min(f, e.cap))) {
          e.cap -= p, adj[e.to][e.rev].cap += p;
          return p;
        }
    }
    return 0;
  }
  ll flow(int s, int t) {
    ll f = 0; q[0] = s;
    for (int it = 29; it >= 0; it--) do {
      lvl = ptr = vi(sz(q));
      int qi = 0, qe = lvl[s] = 1;
      while (qi < qe && !lvl[t]) {
        int v = q[qi++];
        for (edge e : adj[v])
          if (!lvl[e.to] && e.cap >> it)
            q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
      }
      while (ll p = dfs(s, t, LLONG_MAX)) f += p;
    } while (lvl[t]);
    return f;
  }
};

/**
 * Opis: Dinic uproszczony do znajdywania największego skojarzenia.
 * Czas: O(m \sqrt{n})
 */
#pragma once

struct matching {
  vector<vi> adj;
  vi l, r, lvl;
  matching(int n, int m) : adj(n), l(n, -1), r(m, -1) {}
  void add_edge(int u, int v) { adj[u].push_back(v); }
  bool dfs(int u) {
    int t = exchange(lvl[u], -1) + 1;
    for (int v : adj[u])
      if (r[v] == -1 || (lvl[r[v]] == t && dfs(r[v])))
        return l[u] = v, r[v] = u, 1;
    return 0;
  }
  int match() {
    int n = sz(l), ans = 0; vi q(n);
    for (int s = 0, t = 0;; s = t = 0) {
      lvl = vi(n); bool f = 0;
      rep(i, 0, sz(l)) if (l[i] == -1) lvl[i] = 1, q[t++] = i;
      while (s < t) {
        int u = q[s++];
        for (int v : adj[u]) {
          int x = r[v];
          if (x == -1) f = 1;
          else if (!lvl[x]) lvl[x] = lvl[u] + 1, q[t++] = x;
        }
      }
      if (!f) break;
      rep(i, 0, n) if (l[i] == -1) ans += dfs(i);
    }
    return ans;
  }
};

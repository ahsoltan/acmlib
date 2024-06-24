/**
 * Opis: 2-SAT.
 * Czas: O(n + m)
 */
#pragma once

#include "SCC.h"

struct two_sat {
  int n;
  vector<pii> ed;
  vector<bool> b;
  two_sat(int _n) : n(_n) {}
  int add_var() { return n++; }
  void either(int x, int y) {
    x = max(2 * x, -1 - 2 * x), y = max(2 * y, -1 - 2 * y);
    ed.push_back({x, y}); }
  void implies(int x, int y) { either(~x, y); }
  void must(int x) { either(x, x); }
  void at_most_one(const vi& v) {
    if (sz(v) <= 1) return;
    int cur = ~v[0];
    rep(i, 2, sz(v)) {
      int nxt = add_var();
      either(cur, ~v[i]); either(cur, nxt);
      either(~v[i], nxt); cur = ~nxt;
    }
    either(cur, ~v[1]);
  }
  bool solve() {
    SCC scc(2 * n); 
    for (auto [u, v] : ed)
      scc.add_edge(u ^ 1, v), scc.add_edge(v ^ 1, u);
    scc.build(); b.resize(n, 1);
    rep(i, 0, n) {
      if (scc.p[2 * i] == scc.p[2 * i + 1]) return 0;
      if (scc.p[2 * i] < scc.p[2 * i + 1]) b[i] = 0;
    }
    return 1;
  }
};

/**
 * Opis: Tworzy drzewo gdzie min cut to minimum na ścieżce.
 * Czas: O(n) przepływów
 */
#pragma once

#include "Dinic.h"

struct edge { int u, v; ll w; };
vector<edge> gomory_hu(int n, const vector<edge>& ed) {
  vector<edge> t; vi p(n);
  rep(i, 1, n) {
    dinic d(n);
    for (edge e : ed) d.add_edge(e.u, e.v, e.w, e.w);
    t.push_back({i, p[i], d.flow(i, p[i])});
    rep(j, i + 1, n) if (p[j] == p[i] && d.lvl[j]) p[j] = i;
  }
  return t;
}

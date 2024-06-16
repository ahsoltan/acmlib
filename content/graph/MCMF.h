/**
 * Opis: Znajduje największy przepływ o najmniejszym koszcie.
 * Jeżeli są ujemne krawędzie to przed puszczeniem `flow`
 * w `pi` trzeba policzyć najkrótsze ścieżki z `s`.
 * Czas: O(F m \log n)
 */
#pragma once

#include <ext/pb_ds/priority_queue.hpp>
const ll INF = 2e18;
struct MCMF {
  struct edge {
    int from, to, rev;
    ll cap, cost;
  };
  int n;
  vector<vector<edge>> adj;
  vector<ll> dst, pi;
  __gnu_pbds::priority_queue<pair<ll, int>> q;
  vector<decltype(q)::point_iterator> it;
  vector<edge*> p;
  MCMF(int _n) : n(_n), adj(n), pi(n), p(n) {}
  void add_edge(int u, int v, ll cap, ll cost) {
    int i = ssize(adj[u]), j = ssize(adj[v]);
    adj[u].push_back({u, v, j + (u == v), cap, cost});
    adj[v].push_back({v, u, i, 0, -cost});
  }
  bool path(int s, int t) {
    dst.assign(n, INF); it.assign(n, q.end());
    q.push({dst[s] = 0, s});
    while (!q.empty()) {
      int u = q.top().second; q.pop();
      for (edge& e : adj[u]) {
        ll d = dst[u] + pi[u] + e.cost - pi[e.to];
        if (e.cap && d < dst[e.to]) {
          dst[e.to] = d, p[e.to] = &e;
          if (it[e.to] == q.end()) {
            it[e.to] = q.push({-dst[e.to], e.to});
          } else {
            q.modify(it[e.to], {-dst[e.to], e.to});
          }
        }
      }
    }
    for (int i = 0; i < n; i++) {
      pi[i] = min(pi[i] + dst[i], INF);
    }
    return pi[t] != INF;
  }
  pair<ll, ll> flow(int s, int t, ll cap) {
    ll f = 0, c = 0;
    while (f < cap && path(s, t)) {
      ll d = cap - f;
      for (edge* e = p[t]; e; e = p[e->from]) d=min(d, e->cap);
      for (edge* e = p[t]; e; e = p[e->from]) {
        e->cap -= d, adj[e->to][e->rev].cap += d;
      }
      f += d, c += d * pi[t];
    }
    return {f, c};
  }
};

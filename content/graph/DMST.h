/**
 * Opis: Skierowane MST z `r`. Zwraca `{-1, {}}` gdy nie istnieje.
 * Czas: O(m \log m)
 */
#pragma once

#include "RDSU.h"

struct edge { int a, b; ll w; };
struct node {
  edge key;
  node *l = 0, *r = 0;
  ll delta = 0;
  void prop() {
    key.w += delta;
    if (l) l->delta += delta;
    if (r) r->delta += delta;
    delta = 0;
  }
  edge top() { prop(); return key; }
};
node* merge(node* a, node* b) {
  if (!a || !b) return a ?: b;
  a->prop(), b->prop();
  if (a->key.w > b->key.w) swap(a, b);
  swap(a->l, (a->r = merge(b, a->r)));
  return a;
}
void pop(node*& a) { a->prop(); a = merge(a->l, a->r); }
pair<ll, vi> dmst(int n, int r, const vector<edge>& g) {
  RDSU uf(n);
  vector<node*> heap(n);
  for (edge e : g) heap[e.b] = merge(heap[e.b], new node{e});
  ll res = 0;
  vi seen(n, -1), path(n), par(n);
  seen[r] = r;
  vector<edge> Q(n), in(n, {-1, -1, -1}), comp;
  deque<tuple<int, int, vector<edge>>> cycs;
  rep(s, 0, n) {
    int u = s, qi = 0, w;
    while (seen[u] < 0) {
      if (!heap[u]) return {-1, {}};
      edge e = heap[u]->top();
      heap[u]->delta -= e.w, pop(heap[u]);
      Q[qi] = e, path[qi++] = u, seen[u] = s;
      res += e.w, u = uf.find(e.a);
      if (seen[u] == s) {
        node* cyc = 0;
        int end = qi, time = uf.time();
        do cyc = merge(cyc, heap[w = path[--qi]]);
        while (uf.join(u, w));
        u = uf.find(u), heap[u] = cyc, seen[u] = -1;
        cycs.push_front({u, time, {&Q[qi], &Q[end]}});
      }
    }
    rep(i, 0, qi) in[uf.find(Q[i].b)] = Q[i];
  }
  for (auto& [u, t, cmp] : cycs) {
    uf.rollback(t);
    edge inedge = in[u];
    for (auto& e : cmp) in[uf.find(e.b)] = e;
    in[uf.find(inedge.b)] = inedge;
  }
  rep(i, 0, n) par[i] = in[i].a;
  return {res, par};
}

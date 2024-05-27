/**
 * Czas: O(\log n)
 */
#pragma once

mt19937_64 rng(2137);
struct node {
  int val, sz = 1;
  uint64_t pr;
  node *l = 0, *r = 0;
  node(int x) {
    val = x;
    pr = rng();
  }
  void pull() {
    sz = 1 + size(l) + size(r);
  }
  friend int size(node* a) {
    return a ? a->sz : 0;
  }
  friend pair<node*, node*> split(node* a, int k) {
    if (!a) return {0, 0};
    if (k <= size(a->l)) {
      auto [la, lb] = split(a->l, k);
      a->l = lb;
      a->pull();
      return {la, a};
    } else {
      auto [ra, rb] = split(a->r, k - size(a->l) - 1);
      a->r = ra;
      a->pull();
      return {a, rb};
    }
  }
  friend node* merge(node* a, node* b) {
    if (!a || !b) return a ? a : b;
    if (a->pr > b->pr) {
      a->r = merge(a->r, b);
      a->pull();
      return a;
    } else {
      b->l = merge(a, b->l);
      b->pull();
      return b;
    }
  }
};

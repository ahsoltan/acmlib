/**
 * Opis: Implicit treap ze spychaniem.
 * Wystarczy zmienić `push`, `pull` i dane.
 * Czas: O(\log n)
 */
#pragma once

mt19937 rng(2137);
struct node {
  int pr, sz = 1, val;
  node *l = 0, *r = 0;
  ll sum = 0;
  bool rev;
  node(int x = 0) {
    pr = rng();
    sum = val = x;
  }
  void pull() {
    sz = 1 + size(l) + size(r);
    sum = val + (l ? l->sum : 0) + (r ? r->sum : 0);
  }
  void push() {
    if (rev) {
      swap(l, r);
      if (l) l->rev ^= 1;
      if (r) r->rev ^= 1;
      rev = false;
    }
  }
  friend int size(node* a) {
    return a ? a->sz : 0;
  }
  friend pair<node*, node*> split(node* a, int k) {
    if (!a) return {0, 0};
    a->push();
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
    if (!a || !b) return a ?: b;
    a->push(); b->push();
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

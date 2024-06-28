/**
 * Opis: Automat prefiksowy wielu tekstów.
 * Czas: O(n \Sigma)
 */
#pragma once

struct aho {
  enum { alpha = 26, first = 'a' };
  struct node { int go[alpha] = {}, link = 0; };
  vector<node> t = {{}};
  void add(const string& s) {
    int u = 0;
    for (char c : s) {
      int i = c - first;
      if (!t[u].go[i]) {
        t[u].go[i] = sz(t);
        t.emplace_back();
      }
      u = t[u].go[i];
    }
  }
  void build() {
    queue<int> q; q.push(0);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      rep(i, 0, alpha) {
        int& v = t[u].go[i];
        if (!v) v = t[t[u].link].go[i];
        else {
          if (u) t[v].link = t[t[u].link].go[i];
          q.push(v);
        }
      }
    }
  }
};

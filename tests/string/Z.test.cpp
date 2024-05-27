#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "content/string/Z.h"

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  cin >> s;
  auto p = z(s);
  for (int i = 0; i < ssize(s); i++) {
    cout << p[i] << " \n"[i == ssize(s) - 1];
  }
}

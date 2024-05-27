#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "content/string/Manacher.h"

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  cin >> s;
  int n = ssize(s);
  auto p = manacher(s);
  for (int i = 0; i < 2 * n - 1; i++) {
    cout << p[i] << " \n"[i == 2 * n - 2];
  }
}

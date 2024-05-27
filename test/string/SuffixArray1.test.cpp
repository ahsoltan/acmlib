#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "string/SuffixArray.h"

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  cin >> s;
  auto p = suffix_array(s);
  for (int i = 0; i < ssize(s); i++) {
    cout << p[i] << " \n"[i == ssize(s) - 1];
  }
}

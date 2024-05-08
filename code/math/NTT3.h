/**
 * Stosowanie: $n + m \leq 2^{24}$.
 * Czas: O((n + m) \log (n + m))
 */
template<typename T>
vector<T> mconv(const auto& a, const auto& b) {
  auto cp = [&](const auto& v) {
    vector<T> vv(ssize(v));
    for (int i = 0; i < ssize(v); i++) vv[i] = T(v[i].x);
    return vv;
  };
  return conv(cp(a), cp(b));
}
template<typename T>
vector<T> conv3(const vector<T>& a, const vector<T>& b) {
  using m0 = mod<754974721, 11>; auto c0 = mconv<m0>(a, b);
  using m1 = mod<167772161, 3>; auto c1 = mconv<m1>(a, b);
  using m2 = mod<469762049, 3>; auto c2 = mconv<m2>(a, b);
  m1 r01 = m1(m0::MOD).inv();
  m2 r02 = m2(m0::MOD).inv(), r12 = m2(m1::MOD).inv();
  vector<T> d(ssize(c0));
  for (int i = 0; i < ssize(c0); i++) {
    int a = c0[i].x;
    int b = ((c1[i] - a) * r01).x;
    int c = (((c2[i] - a) * r02 - b) * r12).x;
    d[i] = (T(c) * m1::MOD + b) * m0::MOD + a;
  }
  return d;
}

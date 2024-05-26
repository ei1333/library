template <typename T>
vector<tuple<T, T, T> > enumerate_quotients(T n) {
  T l = 1;
  vector<tuple<T, T, T> > quotients;
  while (l <= n) {
    T q = n / l;
    T r = n / q + 1;
    quotients.emplace_back(q, l, r);
    l = r;
  }
  reverse(quotients.begin(), quotients.end());
  return quotients;
}

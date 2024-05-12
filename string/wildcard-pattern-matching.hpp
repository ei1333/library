#include "../math/fft/number-theoretic-transform-friendly-mod-int.hpp"

template <class mint, class S, class T>
std::vector<int> wildcard_pattern_matching(S a, S b, T wildcard) {
  int n = (int)a.size(), m = (int)b.size();
  assert(m <= n);

  vector<mint> as(n), bs(n), cs(n), ss(m), ts(m), us(m);
  for (int i = 0; i < n; i++) {
    mint x(a[i] == wildcard ? 0 : a[i]);
    mint y(a[i] == wildcard ? 0 : 1);
    as[i] = y * x * x;
    bs[i] = y * x * -2;
    cs[i] = y;
  }

  for (int i = 0; i < m; i++) {
    mint x(b[i] == wildcard ? 0 : b[i]);
    mint y(b[i] == wildcard ? 0 : 1);
    ss[m - i - 1] = y;
    ts[m - i - 1] = y * x;
    us[m - i - 1] = y * x * x;
  }

  NumberTheoreticTransformFriendlyModInt<mint> ntt;
  auto f = ntt.multiply(as, ss);
  auto g = ntt.multiply(bs, ts);
  auto h = ntt.multiply(cs, us);

  vector<int> result(n - m + 1);
  for (int i = 0; i < (int)result.size(); i++) {
    int j = i + m - 1;
    mint x(f[j] + g[j] + h[j]);
    result[i] = x.val() == 0;
  }

  return result;
}

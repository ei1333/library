#include "lcp-array.hpp"

template <typename S>
tuple<int, int, int, int> longest_common_substring(const S& s, const S& t,
                                                   bool compress = false) {
  int n = (int)s.size(), m = (int)t.size();
  auto dummy =
      max(*max_element(s.begin(), s.end()), *max_element(t.begin(), t.end()));
  S st;
  st.reserve(n + 1 + m);
  for (auto& x : s) st.push_back(x);
  st.push_back(dummy + 1);
  for (auto& x : t) st.push_back(x);
  SuffixArray sa(st, compress);
  auto lcp = lcp_array(sa);
  tuple<int, int, int, int> res{0, 0, 0, 0};
  int ret = 0;
  for (int i = 0; i < (int)st.size() - 1; i++) {
    int x = sa[i], y = sa[i + 1];
    if (x > y) swap(x, y);
    if (x < n and n < y and ret < lcp[i + 1]) {
      y -= n + 1;
      ret = lcp[i + 1];
      res = {x, x + ret, y, y + ret};
    }
  }
  return res;
}

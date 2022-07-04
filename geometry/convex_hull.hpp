#include "base.hpp"
#include "point.hpp"
#include "polygon.hpp"

namespace geometry {
  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A
  Polygon convex_hull(Polygon &p, bool strict = true) {
    int n = (int) p.size(), k = 0;
    if(n <= 2) return p;
    sort(begin(p), end(p), compare_x);
    vector< Point > ch(2 * n);
    auto check = [&](int i) {
      return sign(cross(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1])) <= -1 + strict;
    };
    for(int i = 0; i < n; ch[k++] = p[i++]) {
      while(k >= 2 && check(i)) --k;
    }
    for(int i = n - 2, t = k + 1; i >= 0; ch[k++] = p[i--]) {
      while(k >= t && check(i)) --k;
    }
    ch.resize(k - 1);
    return ch;
  }
}

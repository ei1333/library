#include "top-tree.hpp"

// verified: https://www.spoj.com/problems/QTREE4/
template <typename T>
struct Diameter {
  static constexpr T m_inf = numeric_limits<T>::min();
  struct Point {
    T dia, dep1, dep2;
  };
  struct Path {
    T dia, all, pref_max, suf_max;
  };
  struct Info {
    bool is_vertex;
    T w;
  };
  static Path vertex(const Info& u) { return add_vertex({m_inf, m_inf}, u); }
  static Path add_vertex(const Point& d, const Info& u) {
    Path p;
    p.dia = d.dia;
    p.pref_max = m_inf;
    p.all = u.w;
    if (d.dep1 != m_inf) {
      p.pref_max = d.dep1 + u.w;
      if (d.dep2 != m_inf) {
        p.dia = max(p.dia, d.dep1 + u.w + d.dep2);
      }
    }
    if (u.is_vertex) {
      p.pref_max = max(p.pref_max, u.w);
      p.dia = max(p.dia, p.pref_max);
    }
    p.suf_max = p.pref_max;
    return p;
  }
  static Point add_edge(const Path& d) { return {d.dia, d.pref_max, m_inf}; }
  static Point rake(Point l, const Point& r) {
    l.dia = max(l.dia, r.dia);
    if (l.dep1 < r.dep1) {
      l.dep2 = max(l.dep1, r.dep2);
      l.dep1 = r.dep1;
    } else {
      l.dep2 = max(l.dep2, r.dep1);
    }
    return l;
  }
  static Path compress(const Path& p, const Path& c) {
    Path t;
    t.dia = max(p.dia, c.dia);
    if (p.suf_max != m_inf and c.pref_max != m_inf) {
      t.dia = max(t.dia, p.suf_max + c.pref_max);
    }
    t.all = p.all + c.all;
    t.pref_max = p.pref_max;
    t.suf_max = c.suf_max;
    if (c.pref_max != m_inf) {
      t.pref_max = max(t.pref_max, p.all + c.pref_max);
    }
    if (p.suf_max != m_inf) {
      t.suf_max = max(t.suf_max, c.all + p.suf_max);
    }
    return t;
  }
};

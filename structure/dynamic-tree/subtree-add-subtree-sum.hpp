#include "lazy-top-tree.hpp"

template <typename T>
struct SubtreeAddSubtreeSum {
  struct Lazy {
    T v;
    static constexpr Lazy id() { return {0}; }
    void propagate(const Lazy& p) { v += p.v; }
  };
  struct Point {
    T sum;
    int sz;
    void propagate(const Lazy& p) { sum += p.v * sz; }
  };
  struct Path {
    T sum;
    int sz;
    void propagate(const Lazy& p) { sum += sz * p.v; }
    void propagate_light(const Lazy& p) {}
  };
  struct Info {
    T v;
    void propagate(const Lazy& p) { v += p.v; }
  };

  static Path vertex(const Info& u) { return {u.v, 1}; }
  static Path add_vertex(const Point& d, const Info& u) {
    return {d.sum + u.v, 1 + d.sz};
  }
  static Point add_edge(const Path& d) { return {d.sum, d.sz}; }
  static Point rake(const Point& l, const Point& r) {
    return {l.sum + r.sum, l.sz + r.sz};
  }
  static Path compress(const Path& p, const Path& c) {
    return {p.sum + c.sum, p.sz + c.sz};
  }
};

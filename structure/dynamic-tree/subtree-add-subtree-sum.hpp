#include "lazy-top-tree.hpp"

struct SubtreeAddSubtreeSum {
  struct Lazy {
    int64 v;
    Lazy() : v{0} {}
    Lazy(int64 v) : v{v} {}
    void propagate(const Lazy& p) { v += p.v; }
  };
  struct Point {
    int64 sum;
    int sz;
    void propagate(const Lazy& p) { sum += p.v * sz; }
  };
  struct Path {
    int64 sum;
    int sz;
    void propagate(const Lazy& p) { sum += sz * p.v; }
    void propagate_light(const Lazy& p) {}
  };
  struct Info {
    int64 v;
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

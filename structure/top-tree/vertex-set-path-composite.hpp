#include "../../math/combinatorics/montgomery-mod-int.hpp"

using mint = modint998244353;

struct VertexSetPathComposite {
  struct Point {};
  struct Path {
    mint a, b;
  };
  struct Info {
    mint x, y;
  };

  static Path vertex(const Info& u) { return {u.x, u.y}; }
  static Path add_vertex(const Point& d, const Info& u) { return {u.x, u.y}; }
  static Point add_edge(const Path& d) { return {}; }
  static Point rake(const Point& l, const Point& r) { return {}; }
  static Path compress(const Path& p, const Path& c) {
    return {p.a * c.a, p.b * c.a + c.b};
  }
};

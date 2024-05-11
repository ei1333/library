#include "link-cut-tree.hpp"

template <typename T>
struct VertexSetPathComposite {
  struct Path {
    T a, b;
  };
  struct Info {
    T x, y;
  };

  static Path vertex(const Info& u) { return {u.x, u.y}; }
  static Path compress(const Path& p, const Path& c) {
    return {p.a * c.a, p.b * c.a + c.b};
  }
};

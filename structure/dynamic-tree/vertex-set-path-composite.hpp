#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "link-cut-tree.hpp"

using mint = modint998244353;

struct VertexSetPathComposite {
  struct Path {
    mint a, b;
  };
  struct Info {
    mint x, y;
  };

  static Path vertex(const Info& u) { return {u.x, u.y}; }
  static Path compress(const Path& p, const Path& c) {
    return {p.a * c.a, p.b * c.a + c.b};
  }
};

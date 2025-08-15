template <typename T, typename T2, typename T3>
struct RangeLinearAddRangeMinSegmentTree {
 private:
  using Point = pair<int, T>;

  struct Node {
    Point lbr, rbr;

    T lza, lzb;

    Node(int x, T y) : lbr{x, y}, rbr{x, y}, lza{0}, lzb{0} {}

    Node() : lza{0}, lzb{0} {}
  };

#define x first
#define y second

  static constexpr T2 cross(const Point& a, const Point& b, const Point& c) {
    return T2(b.y - a.y) * (c.x - a.x) - T2(c.y - a.y) * (b.x - a.x);
  }

  size_t n, sz, height;
  const T ti;
  vector<int> mid;
  vector<Node> seg;

  void update(int k) {
    int l = 2 * k, r = 2 * k + 1;
    int split_x = mid[r];
    propagate(k);
    Point a = seg[l].lbr;
    Point b = seg[l].rbr;
    Point c = seg[r].lbr;
    Point d = seg[r].rbr;
    T lza_l = 0, lzb_l = 0, lza_r = 0, lzb_r = 0;
    auto move_left = [&](bool f) {
      lza_l += seg[l].lza;
      lzb_l += seg[l].lzb;
      l = l * 2 + f;
      a = seg[l].lbr;
      b = seg[l].rbr;
      a.y += lza_l * a.x + lzb_l;
      b.y += lza_l * b.x + lzb_l;
    };
    auto move_right = [&](bool f) {
      lza_r += seg[r].lza;
      lzb_r += seg[r].lzb;
      r = r * 2 + f;
      c = seg[r].lbr;
      d = seg[r].rbr;
      c.y += lza_r * c.x + lzb_r;
      d.y += lza_r * d.x + lzb_r;
    };
    while (l < sz or r < sz) {
      T3 s1 = cross(a, b, c);
      if (l < sz and s1 > 0) {
        move_left(0);
      } else if (r < sz and cross(b, c, d) > 0) {
        move_right(1);
      } else if (l >= sz) {
        move_right(0);
      } else if (r >= sz) {
        move_left(1);
      } else {
        T3 s2 = cross(b, a, d);
        if (s1 + s2 == 0 or s1 * (d.x - split_x) < s2 * (split_x - c.x)) {
          move_left(1);
        } else {
          move_right(0);
        }
      }
    }
    seg[k].lbr = a;
    seg[k].rbr = c;
  }

  void all_apply(int k, T a, T b) {
    seg[k].lbr.y += a * seg[k].lbr.x + b;
    seg[k].rbr.y += a * seg[k].rbr.x + b;
    if (k < sz) seg[k].lza += a, seg[k].lzb += b;
  }

  void propagate(int k) {
    if (seg[k].lza != 0 or seg[k].lzb != 0) {
      all_apply(2 * k, seg[k].lza, seg[k].lzb);
      all_apply(2 * k + 1, seg[k].lza, seg[k].lzb);
      seg[k].lza = seg[k].lzb = 0;
    }
  }

  T min_subtree(int k) {
    T a = 0, b = 0;
    while (k < sz) {
      bool f =
          (seg[k].lbr.y - seg[k].rbr.y) > a * (seg[k].rbr.x - seg[k].lbr.x);
      a += seg[k].lza;
      b += seg[k].lzb;
      k = k * 2 + f;
    }
    return seg[k].lbr.y + a * seg[k].lbr.x + b;
  }

 public:
  explicit RangeLinearAddRangeMinSegmentTree(const vector<T>& vs, const T& ti)
      : n(vs.size()), ti(ti) {
    sz = 1;
    height = 0;
    while (sz < n) sz <<= 1, height++;
    seg.resize(2 * sz);
    mid.resize(2 * sz);
    for (int k = 0; k < sz; k++) {
      seg[sz + k] = Node(k, k < n ? vs[k] : 0);
      mid[sz + k] = k;
    }
    for (int k = sz - 1; k > 0; k--) {
      mid[k] = mid[2 * k];
      update(k);
    }
  }

  T prod(int l, int r) {
    if (l >= r) return ti;
    l += sz;
    r += sz;
    for (int i = height; i > 0; i--) {
      if (((l >> i) << i) != l) propagate(l >> i);
      if (((r >> i) << i) != r) propagate((r - 1) >> i);
    }
    T res = ti;
    while (l < r) {
      if (l & 1) res = min(res, min_subtree(l++));
      if (r & 1) res = min(res, min_subtree(--r));
      l >>= 1;
      r >>= 1;
    }
    return res;
  }

  void apply(int l, int r, T a, T b) {
    if (l >= r) return;
    l += sz;
    r += sz;
    for (int i = height; i > 0; i--) {
      if (((l >> i) << i) != l) propagate(l >> i);
      if (((r >> i) << i) != r) propagate((r - 1) >> i);
    }
    {
      int l2 = l, r2 = r;
      for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) all_apply(l++, a, b);
        if (r & 1) all_apply(--r, a, b);
      }
      l = l2, r = r2;
    }
    for (int i = 1; i <= height; i++) {
      if (((l >> i) << i) != l) update(l >> i);
      if (((r >> i) << i) != r) update((r - 1) >> i);
    }
  }

#undef x
#undef y
};

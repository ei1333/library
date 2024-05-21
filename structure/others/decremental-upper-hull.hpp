template <typename T, typename T2, typename T3>
struct DecrementalUpperHull {
 private:
  using Point = pair<T, T>;
#define x first
#define y second
  static constexpr T2 cross(const Point &a, const Point &b, const Point &c) {
    return T2(b.y - a.y) * (c.x - a.x) - T2(c.y - a.y) * (b.x - a.x);
  }
  struct Node {
    Point l;
    pair<Point, Point> bridge;
    int ch[2];
  };
  size_t root, n, sz;
  vector<Node> seg;
  vector<bool> alive;

  size_t build(size_t &k, int l, int r) {
    if (r - l == 1) return l + n;
    int m = (l + r) / 2;
    size_t res = k++;
    seg[res].ch[0] = build(k, l, m);
    seg[res].ch[1] = build(k, m, r);
    seg[res].l = seg[seg[res].ch[0]].l;
    seg[res].bridge = pull(res);
    return res;
  }

  pair<Point, Point> pull(int k) const {
    int l = seg[k].ch[0], r = seg[k].ch[1];
    Point a = seg[l].bridge.first;
    Point b = seg[l].bridge.second;
    Point c = seg[r].bridge.first;
    Point d = seg[r].bridge.second;
    const T split_x = seg[r].l.first;
    auto move_left = [&](bool f) {
      l = seg[l].ch[f];
      a = seg[l].bridge.first;
      b = seg[l].bridge.second;
    };
    auto move_right = [&](bool f) {
      r = seg[r].ch[f];
      c = seg[r].bridge.first;
      d = seg[r].bridge.second;
    };
    while (l < n or r < n) {
      T3 s1 = cross(a, b, c);
      if (l < n and s1 < 0) {
        move_left(0);
      } else if (r < n and cross(b, c, d) < 0) {
        move_right(1);
      } else if (l >= n) {
        move_right(0);
      } else if (r >= n) {
        move_left(1);
      } else {
        T3 s2 = cross(b, a, d);
        if (s1 + s2 == 0 or s1 * (d.x - split_x) > s2 * (split_x - c.x)) {
          move_left(1);
        } else {
          move_right(0);
        }
      }
    }
    return {a, c};
  }

  void get_hull(int v, const Point &L, const Point &R, vector<int> &res) const {
    if (v >= n) {
      res.emplace_back(v - n);
    } else if (R <= seg[v].bridge.first) {
      get_hull(seg[v].ch[0], L, R, res);
    } else if (seg[v].bridge.second <= L) {
      get_hull(seg[v].ch[1], L, R, res);
    } else {
      get_hull(seg[v].ch[0], L, seg[v].bridge.first, res);
      get_hull(seg[v].ch[1], seg[v].bridge.second, R, res);
    }
  }

 public:
  explicit DecrementalUpperHull(const vector<Point> &ps)
      : n(ps.size()), seg(2 * n), sz(n), alive(n) {
    if (ps.empty()) return;
    assert(is_sorted(ps.begin(), ps.end()));
    for (int k = 0; k < n; k++) {
      seg[k + n] = Node{ps[k], {ps[k], ps[k]}};
    }
    size_t u = 0;
    root = build(u, 0, n);
  }

  size_t size() const { return sz; }

  bool empty() const { return sz == 0; }

  bool erase(int k) {
    assert(sz > 0);
    assert(0 <= k and k < n);
    if (alive[k]) return false;
    alive[k] = true;
    k += n;
    Point &p = seg[k].l;
    sz--;
    static vector<int> buf;
    if (sz > 0) {
      int v = root;
      while (v < n) {
        buf.emplace_back(v);
        v = seg[v].ch[p >= seg[seg[v].ch[1]].l];
      }
      if (buf.size() == 1) {
        buf.pop_back();
        root = seg[root].ch[seg[root].ch[0] == k];
      } else {
        int vp = buf.back();
        buf.pop_back();
        int vpp = buf.back();
        int u = seg[vp].ch[seg[vp].ch[0] == v];
        seg[vpp].ch[seg[vpp].ch[0] != vp] = u;
        while (not buf.empty()) {
          vp = buf.back();
          buf.pop_back();
          seg[vp].l = seg[seg[vp].ch[0]].l;
          if (seg[vp].bridge.first == p || seg[vp].bridge.second == p) {
            seg[vp].bridge = pull(vp);
          }
        }
      }
    }
    return true;
  }

  vector<int> get_hull() {
    if (sz == 0) return {};
    vector<int> res;
    get_hull(root, seg[n].bridge.first, seg[n + n - 1].bridge.first, res);
    return res;
  }
#undef x
#undef y
};

template <typename K, typename Monoid2D>
struct RangeTree {
  using S = typename Monoid2D::S;
  using D = typename Monoid2D::D;

 private:
  vector<vector<K> > ys;
  vector<pair<K, K> > ps;
  vector<K> xs;
  vector<D> ds;
  int n;

  Monoid2D m;

  int id(K x) const {
    return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
  }

  int id(int k, K y) const {
    return lower_bound(ys[k].begin(), ys[k].end(), y) - ys[k].begin();
  }

 public:
  RangeTree() = default;

  explicit RangeTree(Monoid2D m) : m(m) {}

  void add_point(K x, K y) { ps.emplace_back(x, y); }

  void build() {
    sort(ps.begin(), ps.end());
    ps.erase(unique(ps.begin(), ps.end()), ps.end());
    n = (int)ps.size();
    xs.reserve(n);
    for (auto& [x, _] : ps) {
      xs.emplace_back(x);
    }
    ys.resize(2 * n);
    ds.resize(2 * n);
    for (int i = 0; i < n; i++) {
      ys[i + n] = {ps[i].second};
      ds[i + n] = m.init(1);
    }
    for (int i = n - 1; i > 0; i--) {
      ys[i].resize(ys[i << 1].size() + ys[(i << 1) | 1].size());
      merge(ys[i << 1].begin(), ys[i << 1].end(), ys[(i << 1) | 1].begin(),
            ys[(i << 1) | 1].end(), ys[i].begin());
      ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());
      ds[i] = m.init((int)ys[i].size());
    }
  }

  void apply(K x, K y, S a) {
    int k = lower_bound(ps.begin(), ps.end(), make_pair(x, y)) - ps.begin();
    assert(ps[k] == make_pair(x, y));
    k += n;
    while (k > 0) {
      m.apply(ds[k], id(k, y), a);
      k >>= 1;
    }
  }

  S prod(K l, K d, K r, K u) {
    int a = id(l), b = id(r);
    a += n;
    b += n;
    S L = m.e(), R = m.e();
    while (a < b) {
      if (a & 1) {
        L = m.op(L, m.prod(ds[a], id(a, d), id(a, u)));
        ++a;
      }
      if (b & 1) {
        --b;
        R = m.op(m.prod(ds[b], id(b, d), id(b, u)), R);
      }
      a >>= 1;
      b >>= 1;
    }
    return m.op(L, R);
  }
};

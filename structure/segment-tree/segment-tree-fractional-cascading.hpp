template <typename T>
struct SegmentTreeFractionalCascading {
 private:
  vector<vector<T> > seg;
  vector<vector<int> > LL, RR;
  int sz;

  int prod(int a, int b, int lower, int upper, int k, int l, int r) const {
    if (a >= r or b <= l) {
      return 0;
    } else if (a <= l and r <= b) {
      return upper - lower;
    } else {
      return prod(a, b, LL[k][lower], LL[k][upper], 2 * k + 1, l,
                  (l + r) >> 1) +
             prod(a, b, RR[k][lower], RR[k][upper], 2 * k + 2, (l + r) >> 1, r);
    }
  }

 public:
  SegmentTreeFractionalCascading() = default;

  explicit SegmentTreeFractionalCascading(const vector<T> &v) {
    sz = 1;
    while (sz < v.size()) sz <<= 1;
    seg.resize(2 * sz - 1);
    LL.resize(2 * sz - 1);
    RR.resize(2 * sz - 1);
    for (int k = 0; k < v.size(); k++) {
      seg[k + sz - 1].emplace_back(v[k]);
    }
    for (int k = sz - 2; k >= 0; k--) {
      seg[k].resize(seg[2 * k + 1].size() + seg[2 * k + 2].size());
      LL[k].resize(seg[k].size() + 1);
      RR[k].resize(seg[k].size() + 1);
      merge(seg[2 * k + 1].begin(), seg[2 * k + 1].end(),
            seg[2 * k + 2].begin(), seg[2 * k + 2].end(), seg[k].begin());
      int tail1 = 0, tail2 = 0;
      for (int i = 0; i < seg[k].size(); i++) {
        while (tail1 < seg[2 * k + 1].size() and
               seg[2 * k + 1][tail1] < seg[k][i])
          ++tail1;
        while (tail2 < seg[2 * k + 2].size() and
               seg[2 * k + 2][tail2] < seg[k][i])
          ++tail2;
        LL[k][i] = tail1, RR[k][i] = tail2;
      }
      LL[k][seg[k].size()] = (int)seg[2 * k + 1].size();
      RR[k][seg[k].size()] = (int)seg[2 * k + 2].size();
    }
  }

  int prod(int a, int b, T l, T r) const {
    l = int(lower_bound(seg[0].begin(), seg[0].end(), l) - seg[0].begin());
    r = int(lower_bound(seg[0].begin(), seg[0].end(), r) - seg[0].begin());
    return prod(a, b, l, r, 0, 0, sz);
  }
};

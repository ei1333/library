template< typename T, int MAXLOG, typename D >
struct WaveletMatrixRectangleSum {
  size_t length;
  SuccinctIndexableDictionary matrix[MAXLOG];
  vector< D > ds[MAXLOG];
  int mid[MAXLOG];

  WaveletMatrixRectangleSum(const vector< T > &v, const vector< D > &d) : length(v.size()) {
    assert(v.size() == d.size());
    vector< int > l(length), r(length), ord(length);
    iota(begin(ord), end(ord), 0);
    for(int level = MAXLOG - 1; level >= 0; level--) {
      matrix[level] = SuccinctIndexableDictionary(length + 1);
      int left = 0, right = 0;
      for(int i = 0; i < length; i++) {
        if(((v[ord[i]] >> level) & 1)) {
          matrix[level].set(i);
          r[right++] = ord[i];
        } else {
          l[left++] = ord[i];
        }
      }
      mid[level] = left;
      matrix[level].build();
      ord.swap(l);
      for(int i = 0; i < right; i++) {
        ord[left + i] = r[i];
      }
      ds[level].resize(length + 1);
      ds[level][0] = D();
      for(int i = 0; i < length; i++) {
        ds[level][i + 1] = ds[level][i] + d[ord[i]];
      }
    }
  }

  pair< int, int > succ(bool f, int l, int r, int level) {
    return {matrix[level].rank(f, l) + mid[level] * f, matrix[level].rank(f, r) + mid[level] * f};
  }

  // count d[i] s.t. (l <= i < r) && (v[i] < upper)
  D range_sum(int l, int r, T upper) {
    D ret = 0;
    for(int level = MAXLOG - 1; level >= 0; level--) {
      bool f = ((upper >> level) & 1);
      if(f) ret += ds[level][matrix[level].rank(false, r)] - ds[level][matrix[level].rank(false, l)];
      tie(l, r) = succ(f, l, r, level);
    }
    return ret;
  }

  D range_sum(int l, int r, T lower, T upper) {
    return range_sum(l, r, upper) - range_sum(l, r, lower);
  }
};


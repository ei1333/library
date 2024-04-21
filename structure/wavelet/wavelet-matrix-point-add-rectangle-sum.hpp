#include "succinct-indexable-dictionary.hpp"
#include "../others/binary-indexed-tree.hpp"

/*
 * @brief Wavelet Matrix Point Add Rectangle Sum
 * 
 */
template< typename T, int MAXLOG, typename D >
struct WaveletMatrixPointAddRectangleSum {
  size_t length;
  SuccinctIndexableDictionary matrix[MAXLOG];
  BinaryIndexedTree< D > ds[MAXLOG];
  vector< T > v;
  int mid[MAXLOG];

  WaveletMatrixPointAddRectangleSum() = default;

  WaveletMatrixPointAddRectangleSum(const vector< T > &v, const vector< D > &d) : length(v.size()), v(v) {
    assert(v.size() == d.size());
    vector< int > l(length), r(length), ord(length);
    iota(begin(ord), end(ord), 0);
    vector< D > dd(length);
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
      for(int i = 0; i < length; i++) {
        dd[i] = d[ord[i]];
      }
      ds[level] = BinaryIndexedTree< D >(dd);
    }
  }

  pair< int, int > succ(bool f, int l, int r, int level) {
    return {matrix[level].rank(f, l) + mid[level] * f, matrix[level].rank(f, r) + mid[level] * f};
  }

  // count d[i] s.t. (l <= i < r) && (v[i] < upper)
  D rect_sum(int l, int r, T upper) {
    D ret = 0;
    for(int level = MAXLOG - 1; level >= 0; level--) {
      if(((upper >> level) & 1)) {
        auto nxt = succ(false, l, r, level);
        ret += ds[level].prod(nxt.first, nxt.second);
        l = l - nxt.first + mid[level];
        r = r - nxt.second + mid[level];
      } else {
        tie(l, r) = succ(false, l, r, level);
      }
    }
    return ret;
  }

  D rect_sum(int l, int r, T lower, T upper) {
    return rect_sum(l, r, upper) - rect_sum(l, r, lower);
  }

  void point_add(int k, const D &x) {
    auto &y = v[k];
    for(int level = MAXLOG - 1; level >= 0; level--) {
      bool f = ((y >> level) & 1);
      k = matrix[level].rank(f, k) + mid[level] * f;
      ds[level].apply(k, x);
    }
  }
};

template< typename T, int MAXLOG, typename D >
struct CompressedWaveletMatrixPointAddRectangleSum {
  WaveletMatrixPointAddRectangleSum< int, MAXLOG, D > mat;
  vector< T > ys;

  CompressedWaveletMatrixPointAddRectangleSum(const vector< T > &v, const vector< D > &d) : ys(v) {
    sort(begin(ys), end(ys));
    ys.erase(unique(begin(ys), end(ys)), end(ys));
    vector< int > t(v.size());
    for(int i = 0; i < v.size(); i++) t[i] = get(v[i]);
    mat = WaveletMatrixPointAddRectangleSum< int, MAXLOG, D >(t, d);
  }

  inline int get(const T &x) {
    return lower_bound(begin(ys), end(ys), x) - begin(ys);
  }

  D rect_sum(int l, int r, T upper) {
    return mat.rect_sum(l, r, get(upper));
  }

  D rect_sum(int l, int r, T lower, T upper) {
    return mat.rect_sum(l, r, get(lower), get(upper));
  }

  void point_add(int k, const D &x) {
    mat.point_add(k, x);
  }
};

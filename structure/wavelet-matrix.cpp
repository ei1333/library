struct SuccinctIndexableDictionary {
  size_t length;
  size_t blocks;
  vector< unsigned > bit, sum;

  SuccinctIndexableDictionary() {
  }

  SuccinctIndexableDictionary(size_t _length) {
    length = _length;
    blocks = (length + 31) >> 5;
    bit.assign(blocks, 0U);
    sum.assign(blocks, 0U);
  }

  void set(int k) {
    bit[k >> 5] |= 1U << (k & 31);
  }

  void build() {
    sum[0] = 0U;
    for(int i = 1; i < blocks; i++) {
      sum[i] = sum[i - 1] + __builtin_popcount(bit[i - 1]);
    }
  }

  bool operator[](int k) const {
    return (bool((bit[k >> 5] >> (k & 31)) & 1));
  }

  int rank(int k) {
    return (sum[k >> 5] + __builtin_popcount(bit[k >> 5] & ((1U << (k & 31)) - 1)));
  }

  int rank(bool val, int k) {
    return (val ? rank(k) : k - rank(k));
  }

  int select(bool val, int k) {
    if(k < 0 || rank(val, length) <= k) return (-1);
    int low = 0, high = length;
    while(high - low > 1) {
      int mid = (low + high) >> 1;
      if(rank(val, mid) >= k + 1) high = mid;
      else low = mid;
    }
    return (high - 1);
  }

  int select(bool val, int i, int l) {
    return select(val, i + rank(val, l));
  }
};

template< class T, int MAXLOG >
struct WaveletMatrix {
  size_t length;
  SuccinctIndexableDictionary matrix[MAXLOG];
  int zs[MAXLOG];
  int buff1[MAXLOG], buff2[MAXLOG];

  int freq_dfs(int d, int l, int r, T val, T a, T b) {
    if(l == r) return 0;
    if(d == MAXLOG) return (a <= val && val < b) ? r - l : 0;
    T nv = 1ULL << (MAXLOG - d - 1) | val, nnv = ((1ULL << (MAXLOG - d - 1)) - 1) | nv;
    if(nnv < a || b <= val) return 0;
    if(a <= val && nnv < b) return r - l;
    int lc = matrix[d].rank(1, l), rc = matrix[d].rank(1, r);
    return freq_dfs(d + 1, l - lc, r - rc, val, a, b) +
           freq_dfs(d + 1, lc + zs[d], rc + zs[d], nv, a, b);
  }

  WaveletMatrix(vector< T > data) {
    length = data.size();
    vector< T > l(length), r(length);
    for(int depth = 0; depth < MAXLOG; depth++) {
      matrix[depth] = SuccinctIndexableDictionary(length + 1);
      int left = 0, right = 0;
      for(int i = 0; i < length; i++) {
        bool k = (data[i] >> (MAXLOG - depth - 1)) & 1;
        if(k) r[right++] = data[i], matrix[depth].set(i);
        else l[left++] = data[i];
      }
      zs[depth] = left;
      matrix[depth].build();
      swap(l, data);
      for(int i = 0; i < right; i++) data[left + i] = r[i];
    }
  }

  T access(int k) {
    int ret = 0;
    bool bit;
    for(int depth = 0; depth < MAXLOG; depth++) {
      bit = matrix[depth][k];
      ret = (ret << 1) | bit;
      k = matrix[depth].rank(bit, k) + zs[depth] * bit;
    }
    return (ret);
  }

  int rank(T val, int k) {
    int l = 0, r = k;
    for(int depth = 0; depth < MAXLOG; depth++) {
      buff1[depth] = l, buff2[depth] = r;
      bool bit = (val >> (MAXLOG - depth - 1)) & 1;
      l = matrix[depth].rank(bit, l) + zs[depth] * bit;
      r = matrix[depth].rank(bit, r) + zs[depth] * bit;
    }
    return (r - l);
  }

  int select(T val, int kth) {
    rank(val, length);
    for(int depth = MAXLOG - 1; depth >= 0; depth--) {
      bool bit = (val >> (MAXLOG - depth - 1)) & 1;
      kth = matrix[depth].select(bit, kth, buff1[depth]);
      if(kth >= buff2[depth] || kth < 0) return (-1);
      kth -= buff1[depth];
    }
    return (kth);
  }

  int select(T val, int k, int l) {
    return select(val, k + rank(val, l));
  }

  int quantile(int left, int right, int kth) {
    if(right - left <= kth || kth < 0) return (-1);
    T ret = 0;
    for(int depth = 0; depth < MAXLOG; depth++) {
      int l = matrix[depth].rank(1, left);
      int r = matrix[depth].rank(1, right);
      if(r - l > kth) {
        left = l + zs[depth];
        right = r + zs[depth];
        ret |= 1ULL << (MAXLOG - depth - 1);
      } else {
        kth -= r - l;
        left -= l;
        right -= r;
      }
    }
    return ret;
  }
  
  int rangefreq(int left, int right, T lower, T upper) {
    return freq_dfs(0, left, right, 0, lower, upper);
  }
};


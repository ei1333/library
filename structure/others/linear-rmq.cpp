/**
 * @brief Linear-RMQ
 **/
template< typename Comp >
struct LinearRMQ {
  static constexpr int BLOCKSIZE = 16;
  using block_type = uint_least16_t;

  vector< block_type > small;
  vector< vector< int > > large;

  LinearRMQ() = default;

  Comp comp;

  static inline int msb(int c) {
    return 31 - __builtin_clz(c);
  }

  static inline int ctz(int c) {
    return __builtin_ctz(c);
  }

  inline int get_min(int l, int r) const {
    return comp(l, r) ? l : r;
  }

  explicit LinearRMQ(size_t n, const Comp &comp) : comp(comp) {
    vector< int > st;
    st.reserve(BLOCKSIZE);
    large.emplace_back();
    large.front().reserve(n / BLOCKSIZE);
    small.reserve(n);
    for(int i = 0; i < n; i++) {
      while(!st.empty() && !comp(st.back(), i)) {
        st.pop_back();
      }
      small.emplace_back(st.empty() ? 0 : small[st.back()]);
      small.back() |= static_cast< block_type  >(1) << (i % BLOCKSIZE);
      st.emplace_back(i);
      if((i + 1) % BLOCKSIZE == 0) {
        large.front().emplace_back(st.front());
        st.clear();
      }
    }
    for(int i = 1; (i << 1) <= n / BLOCKSIZE; i <<= 1) {
      vector< int > v;
      int csz = n / BLOCKSIZE + 1 - (i << 1);
      v.reserve(csz);
      for(int k = 0; k < csz; k++) {
        v.emplace_back(get_min(large.back()[k], large.back()[k + i]));
      }
      large.emplace_back(move(v));
    }
  }

  int fold(int l, int r) const {
    --r;
    int left = l / BLOCKSIZE + 1;
    int right = r / BLOCKSIZE;
    if(left < right) {
      auto p = msb(right - left);
      return get_min(
          get_min((left - 1) * BLOCKSIZE + ctz(small[left * BLOCKSIZE - 1] & ~static_cast<block_type>(0) << l % BLOCKSIZE), large[p][left]),
          get_min(large[p][right - (1 << p)], right * BLOCKSIZE + ctz(small[r])));
    } else if(left == right) {
      return get_min((left - 1) * BLOCKSIZE + ctz(small[left * BLOCKSIZE - 1] & ~static_cast<block_type>(0) << l % BLOCKSIZE),
                     left * BLOCKSIZE + ctz(small[r]));
    } else {
      return right * BLOCKSIZE + ctz(small[r] & ~static_cast<block_type>(0) << l % BLOCKSIZE);
    }
  }
};

template< typename Comp >
LinearRMQ< Comp > get_linear_rmq(int n, const Comp &comp) {
  return LinearRMQ< Comp >(n, comp);
}

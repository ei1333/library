template< typename T, typename E = int >
struct SqrtDecomposition {

  vector< E > block_add, elem_add;
  vector< int > block_pos;
  vector< T > data, lsum;
  vector< vector< T > > sum;
  int N, B, K;
  E L;

  SqrtDecomposition(int N, E L = 0) : N(N), L(L) { // find the sum of L or more in the interval
    B = (int) sqrt(N);
    K = (N + B - 1) / B;

    block_add.assign(K, 0);
    block_pos.resize(N);
    for(int k = 0; k < K; k++) {
      for(int i = k * B; i < min((k + 1) * B, N); i++) block_pos[i] = k;
    }
    elem_add.assign(N, 0);
    data.assign(N, 0);
    sum.assign(K, vector< T >(B, 0));
    lsum.assign(K, 0);
  }


  void build(const vector< E > &add, const vector< T > &dat) {
    assert(add.size() == elem_add.size());
    assert(dat.size() == data.size());
    elem_add = add;
    data = dat;
    for(int k = 0; k < K; k++) {
      E tap = elem_add[k * B];
      for(int i = k * B; i < min((k + 1) * B, N); i++) tap = min(tap, elem_add[i]);
      block_add[k] = tap;
      for(int i = k * B; i < min((k + 1) * B, N); i++) {
        elem_add[i] -= block_add[k];
        set(i, dat[i]);
      }
    }
  }

  inline void del(int k) {
    sum[block_pos[k]][elem_add[k]] -= data[k];
    if(block_add[block_pos[k]] + elem_add[k] >= L) lsum[block_pos[k]] -= data[k];
  }

  inline void set(int k) {
    while(sum[block_pos[k]].size() <= elem_add[k]) sum[block_pos[k]].push_back(0);
    sum[block_pos[k]][elem_add[k]] += data[k];
    if(block_add[block_pos[k]] + elem_add[k] >= L) lsum[block_pos[k]] += data[k];
  }

  void set(int k, T x) {
    data[k] = x;
    set(k);
  }

  void add(int a, int b) {
    for(int k = 0; k < K; k++) {
      int l = k * B;
      int r = min(l + B, N);

      if(r <= a || b <= l) {

      } else if(a <= l && r <= b) {
        block_add[k]++;
        if(0 <= L - block_add[k] && L - block_add[k] < sum[k].size()) {
          lsum[k] += sum[k][L - block_add[k]];
        }
      } else {
        for(int i = max(a, l); i < min(b, r); i++) {
          del(i);
          elem_add[i]++;
          set(i);
        }
      }
    }
  }


  void sub(int a, int b) {
    for(int k = 0; k < K; k++) {
      int l = k * B;
      int r = min(l + B, N);

      if(r <= a || b <= l) {

      } else if(a <= l && r <= b) {
        if(0 <= L - block_add[k] && L - block_add[k] < sum[k].size()) {
          lsum[k] -= sum[k][L - block_add[k]];
        }
        block_add[k]--;
      } else {
        if(0 <= L - block_add[k] && L - block_add[k] < sum[k].size()) {
          lsum[k] -= sum[k][L - block_add[k]];
        }
        block_add[k]--;
        for(int i = l; i < max(a, l); i++) {
          del(i);
          elem_add[i]++;
          set(i);
        }
        for(int i = min(b, r); i < r; i++) {
          del(i);
          elem_add[i]++;
          set(i);
        }
      }
    }
  }


  T query(int a, int b, E x) {
    T ret = 0;
    for(int k = 0; k < K; k++) {
      int l = k * B;
      int r = min(l + B, N);

      if(r <= a || b <= l) {

      } else if(a <= l && r <= b) {
        if(0 <= x - block_add[k] && x - block_add[k] < sum[k].size()) {
          ret += sum[k][x - block_add[k]];
        }
      } else {
        for(int i = max(a, l); i < min(b, r); i++) {
          if(block_add[k] + elem_add[i] == x) ret += data[i];
        }
      }
    }
    return ret;
  }


  T query_low(int a, int b) {
    T ret = 0;
    for(int k = 0; k < K; k++) {
      int l = k * B;
      int r = min(l + B, N);

      if(r <= a || b <= l) {

      } else if(a <= l && r <= b) {
        ret += lsum[k];
      } else {
        for(int i = max(a, l); i < min(b, r); i++) {
          if(block_add[k] + elem_add[i] >= L) ret += data[i];
        }
      }
    }
    return ret;
  }
};

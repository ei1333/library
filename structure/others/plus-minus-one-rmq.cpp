#include "sparse-table.cpp"

/**
 * @brief Plus-Minus-One-RMQ
 **/
template< typename T >
struct PlusMinusOneRMQ {
  using F = function< int(int, int) >;

  int backet;
  vector< T > vs;
  vector< int > bidx, bbit;
  SparseTable< int, F > st;
  vector< vector< vector< int > > > lookup;

  explicit PlusMinusOneRMQ() = default;

  explicit PlusMinusOneRMQ(const vector< T > &vs) : vs(vs) {
    int n = (int) vs.size();
    backet = max(1, (31 - __builtin_clz(n)) / 2);
    int sz = (n + backet - 1) / backet;
    bidx.assign(sz, -1);
    bbit.assign(sz, 0);
    for(int i = 0; i < sz; i++) {
      int l = i * backet;
      int r = min(l + backet, n);
      bidx[i] = l;
      for(int j = l + 1; j < r; j++) {
        if(vs[j] < vs[bidx[i]]) bidx[i] = j;
        if(vs[j - 1] < vs[j]) bbit[i] |= 1 << (j - l - 1);
      }
    }
    F f = [&](int a, int b) { return vs[a] < vs[b] ? a : b; };
    st = get_sparse_table(bidx, f);
    lookup.assign(1 << (backet - 1), vector< vector< int > >(backet, vector< int >(backet + 1)));
    for(int i = 0; i < (1 << (backet - 1)); i++) {
      for(int j = 0; j < backet; j++) {
        int sum = 0, ret = 0, pos = j;
        for(int k = j + 1; k <= backet; k++) {
          lookup[i][j][k] = pos;
          if(i & (1 << (k - 1))) ++sum;
          else --sum;
          if(sum < ret) {
            pos = k;
            ret = sum;
          }
        }
      }
    }
  }

  pair< T, int > fold(int l, int r) const {
    int lb = l / backet;
    int rb = r / backet;
    if(lb == rb) {
      int pos = lb * backet + lookup[bbit[lb]][l % backet][r % backet];
      return {vs[pos], pos};
    }
    int pos = lb * backet + lookup[bbit[lb]][l % backet][backet];
    if(r % backet > 0) {
      int sub = rb * backet + lookup[bbit[rb]][0][r % backet];
      if(vs[sub] < vs[pos]) pos = sub;
    }
    if(lb + 1 == rb) {
      return {vs[pos], pos};
    } else {
      int sub = st.fold(lb + 1, rb);
      if(vs[sub] < vs[pos]) pos = sub;
      return {vs[pos], pos};
    }
  }
};

/**
 * @brief Sparse-Table(スパーステーブル)
 * @docs docs/sparse-table.md
 */
template< typename T >
struct SparseTable {
  vector< vector< T > > st;
  vector< int > lookup;

  explicit SparseTable(const vector< T > &v) {
    int b = 0;
    while((1 << b) <= v.size()) ++b;
    st.assign(b, vector< T >(1 << b));
    for(int i = 0; i < v.size(); i++) {
      st[0][i] = v[i];
    }
    for(int i = 1; i < b; i++) {
      for(int j = 0; j + (1 << i) <= (1 << b); j++) {
        st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
      }
    }
    lookup.resize(v.size() + 1);
    for(int i = 2; i < lookup.size(); i++) {
      lookup[i] = lookup[i >> 1] + 1;
    }
  }

  inline T query(int l, int r) const {
    int b = lookup[r - l];
    return min(st[b][l], st[b][r - (1 << b)]);
  }
};

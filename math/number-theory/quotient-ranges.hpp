/**
 * @brief Quotient Ranges(商列挙)
 * 
 */
template< typename T >
vector< pair< pair< T, T >, T > > quotient_ranges(T N) {
  vector< pair< pair< T, T >, T > > ret;
  T l = 1;
  while(l <= N) {
    T q = N / l;
    T r = N / q + 1;
    ret.emplace_back(make_pair(l, r), q);
    l = r;
  }
  return ret;
}

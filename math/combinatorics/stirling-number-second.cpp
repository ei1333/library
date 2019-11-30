template< typename T >
T stirling_number_second(int n, int k) {
  Combination< T > table(k);
  T ret = 0;
  for(int i = 0; i <= k; i++) {
    auto add = T(i).pow(n) * table.C(k, i);
    if((k - i) & 1) ret -= add;
    else ret += add;
  }
  return ret * table.rfact(k);
}


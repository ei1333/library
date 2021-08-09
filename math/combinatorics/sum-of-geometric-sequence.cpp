/**
 * @brief Sum of Geometric Sequence(等比数列の和)
 */
template< typename Mint >
Mint sum_of_geometric_sequence(const Mint &a, const Mint &r, const int64_t &n) {
  assert(r != Mint(0));
  return r == Mint(1) ? a * n : a * (r.pow(n) - 1) / (r - 1);
}

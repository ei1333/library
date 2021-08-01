/**
 * @brief Sum of Geometric Sequence(等比数列の和)
 */
template< typename Mint >
Mint sum_of_geometric_sequence(const Mint &a, const Mint &r, const Mint &n) {
  return r == Mint(1) ? a * n : a * (r.pow(n) - 1) / (r - 1);
}

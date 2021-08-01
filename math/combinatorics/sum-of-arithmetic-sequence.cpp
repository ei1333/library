/**
 * @brief Sum of Arithmetic Sequence(等差数列の和)
 */
template< typename Mint >
Mint sum_of_arithmetic_sequence(const Mint &a, const Mint &d, const Mint &n) {
  return n * (2 * a + (n - 1) * d) / 2;
}

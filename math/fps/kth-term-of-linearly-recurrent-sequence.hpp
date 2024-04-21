#include "coeff-of-rational-function.hpp"

/**
 * @brief Kth Term of Linearly Recurrent Sequence
 * 
 */
template< template< typename > class FPS, typename Mint >
Mint kth_term_of_linearly_recurrent_sequence(const FPS< Mint > &a, FPS< Mint > c, int64_t k) {
  assert(a.size() == c.size());
  c = FPS< Mint >{1} - (c << 1);
  return coeff_of_rational_function((a * c).pre(a.size()), c, k);
}

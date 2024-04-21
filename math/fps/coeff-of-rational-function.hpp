/**
 * @brief Coeff of Rational Function
 * 
 */
template< template< typename > class FPS, typename Mint >
Mint coeff_of_rational_function(FPS< Mint > P, FPS< Mint > Q, int64_t k) {
  // compute the coefficient [x^k] P/Q of rational power series
  Mint ret = 0;
  if(P.size() >= Q.size()) {
    auto R = P / Q;
    P -= R * Q;
    P.shrink();
    if(k < (int) R.size()) ret += R[k];
  }
  if(P.empty()) return ret;
  P.resize((int) Q.size() - 1);
  auto sub = [&](const FPS< Mint > &as, bool odd) {
    FPS< Mint > bs((as.size() + !odd) / 2);
    for(int i = odd; i < (int) as.size(); i += 2) bs[i >> 1] = as[i];
    return bs;
  };
  while(k > 0) {
    auto Q2(Q);
    for(int i = 1; i < (int) Q2.size(); i += 2) Q2[i] = -Q2[i];
    P = sub(P * Q2, k & 1);
    Q = sub(Q * Q2, 0);
    k >>= 1;
  }
  return ret + P[0];
}

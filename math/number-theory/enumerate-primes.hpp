#include "prime-table.hpp"

vector< int > enumerate_primes(int n) {
  if(n <= 1) return {};
  auto d = prime_table(n);
  vector< int > primes;
  primes.reserve(count(begin(d), end(d), true));
  for(int i = 0; i < d.size(); i++) {
    if(d[i]) primes.push_back(i);
  }
  return primes;
}

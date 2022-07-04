#include "kth-root-integer.cpp"
#include "prime-table.cpp"

/**
 * @brief Prime Count(素数の個数)
 */
template< int64_t LIM = 100000000000LL >
struct PrimeCount {
private:
  int64_t sq;
  vector< bool > prime;
  vector< int64_t > prime_sum, primes;

  int64_t p2(int64_t x, int64_t y) {
    if(x < 4) return 0;
    int64_t a = pi(y);
    int64_t b = pi(kth_root_integer(x, 2));
    if(a >= b) return 0;
    int64_t sum = (a - 2) * (a + 1) / 2 - (b - 2) * (b + 1) / 2;
    for(int64_t i = a; i < b; i++) sum += pi(x / primes[i]);
    return sum;
  }

  int64_t phi(int64_t m, int64_t n) {
    if(m < 1) return 0;
    if(n > m) return 1;
    if(n < 1) return m;
    if(m <= primes[n - 1] * primes[n - 1]) return pi(m) - n + 1;
    if(m <= primes[n - 1] * primes[n - 1] * primes[n - 1] && m <= sq) {
      int64_t sx = pi(kth_root_integer(m, 2));
      int64_t ans = pi(m) - (sx + n - 2) * (sx - n + 1) / 2;
      for(int64_t i = n; i < sx; ++i) ans += pi(m / primes[i]);
      return ans;
    }
    return phi(m, n - 1) - phi(m / primes[n - 1], n - 1);
  }

public:

  PrimeCount() : sq(kth_root_integer(LIM, 2)), prime_sum(sq + 1) {
    prime = prime_table(sq);
    for(int i = 1; i <= sq; i++) prime_sum[i] = prime_sum[i - 1] + prime[i];
    primes.reserve(prime_sum[sq]);
    for(int i = 1; i <= sq; i++) if(prime[i]) primes.push_back(i);
  }

  int64_t pi(int64_t n) {
    if(n <= sq) return prime_sum[n];
    int64_t m = kth_root_integer(n, 3);
    int64_t a = pi(m);
    return phi(n, a) + a - 1 - p2(n, m);
  }
};

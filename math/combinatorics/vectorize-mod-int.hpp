#include <immintrin.h>
#pragma GCC target ("avx2")

struct alignas(32) VectorizeModInt {
  using Mints = VectorizeModInt;
  using i32 = int32_t;
  using i64 = int64_t;
  using u32 = uint32_t;
  using u64 = uint64_t;

  static __m256i m0, m1, m2, r1;

  template< typename Mint >
  static void set_mod() {
    r1 = _mm256_set1_epi32(Mint::r);
    m0 = _mm256_setzero_si256();
    m1 = _mm256_set1_epi32(Mint::get_mod());
    m2 = _mm256_set1_epi32(Mint::get_mod() * 2);
  }

  __m256i x;

  VectorizeModInt() : x{} {}

  inline VectorizeModInt(const i32 &v) : x(_mm256_set1_epi32(v)) {}

  inline VectorizeModInt(const i32 &v0, const i32 &v1, const i32 &v2, const i32 &v3,
                         const i32 &v4, const i32 &v5, const i32 &v6, const i32 &v7) :
      x(_mm256_setr_epi32(v0, v1, v2, v3, v4, v5, v6, v7)) {}

  inline VectorizeModInt(const void *vs) : x(_mm256_loadu_si256((__m256i *) vs)) {}

  inline VectorizeModInt(const __m256i &x) : x(x) {}

  inline void store(const void *vs) {
    _mm256_storeu_si256((__m256i *) vs, x);
  }

  static inline __m256i _mm256_mulhi_epi32(const __m256i &a, const __m256i &b) {
    auto prod02 = _mm256_mul_epu32(a, b);
    auto prod13 = _mm256_mul_epu32(_mm256_shuffle_epi32(a, 0xf5), _mm256_shuffle_epi32(b, 0xf5));
    return _mm256_unpackhi_epi64(_mm256_unpacklo_epi32(prod02, prod13), _mm256_unpackhi_epi32(prod02, prod13));
  }

  static inline __m256i reduce(const __m256i &lo, const __m256i &hi) {
    // u32(b >> 32) + mod - u32((u64(u32(b) * r) * mod) >> 32)
    return _mm256_add_epi32(_mm256_sub_epi32(hi, _mm256_mulhi_epi32(_mm256_mullo_epi32(lo, r1), m1)), m1);
  }

  Mints inline &operator+=(const Mints &p) {
    // if(int(x += p.x - 2 * mod) < 0) x += 2 * mod;
    const auto c = _mm256_sub_epi32(_mm256_add_epi32(x, p.x), m2);
    x = _mm256_add_epi32(c, _mm256_and_si256(_mm256_cmpgt_epi32(m0, c), m2));
    return *this;
  }


  Mints inline &operator-=(const Mints &p) {
    // if(int(x -= p.x) < 0) x += 2 * mod;
    const auto c = _mm256_sub_epi32(x, p.x);
    x = _mm256_add_epi32(c, _mm256_and_si256(_mm256_cmpgt_epi32(m0, c), m2));
    return *this;
  }

  Mints inline &operator*=(const Mints &p) {
    x = reduce(_mm256_mullo_epi32(x, p.x), _mm256_mulhi_epi32(x, p.x));
    return *this;
  }

  Mints inline operator+(const Mints &p) const { return Mints(*this) += p; }

  Mints inline operator-(const Mints &p) const { return Mints(*this) -= p; }

  Mints inline operator*(const Mints &p) const { return Mints(*this) *= p; }
};

__attribute__((aligned(32))) __m256i VectorizeModInt::m0;
__attribute__((aligned(32))) __m256i VectorizeModInt::m1;
__attribute__((aligned(32))) __m256i VectorizeModInt::m2;
__attribute__((aligned(32))) __m256i VectorizeModInt::r1;

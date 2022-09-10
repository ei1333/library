#include <immintrin.h>

/**
 * @brief Superset Zeta/Moebius Transform SIMD (上位集合のゼータ/メビウス変換, SIMD)
 */
__attribute__((target("avx2")))
void superset_zeta_transform_simd(int *buf, int mod, int n) {
  assert((n & (n - 1)) == 0);
  auto m_zero = _mm256_set1_epi32(0);
  auto m_mod_one = _mm256_set1_epi32(mod - 1);
  auto m_mod = _mm256_set1_epi32(mod);
  auto m_zero2 = _mm_set1_epi32(0);
  auto m_mod_one2 = _mm_set1_epi32(mod - 1);
  auto m_mod2 = _mm_set1_epi32(mod);
  for(int i = 1; i < n; i <<= 1) {
    for(int j = 0; j < n; j += i << 1) {
      if(i <= 2) {
        for(int k = 0; k < i; k++) {
          buf[j + k] += buf[j + k + i];
          if(buf[j + k] >= mod) buf[j + k] -= mod;
        }
      } else if(i == 4) {
        for(int k = 0; k < i; k += 4) {
          auto a = _mm_loadu_si128((__m128i *) (buf + j + k));
          auto b = _mm_loadu_si128((__m128i *) (buf + j + k + i));
          a = _mm_add_epi32(a, b);
          a = _mm_sub_epi32(a, _mm_and_si128(_mm_cmpgt_epi32(a, m_mod_one2), m_mod2));
          _mm_storeu_si128((__m128i *) (buf + j + k), a);
        }
      } else {
        for(int k = 0; k < i; k += 8) {
          auto a = _mm256_loadu_si256((__m256i *) (buf + j + k));
          auto b = _mm256_loadu_si256((__m256i *) (buf + j + k + i));
          a = _mm256_add_epi32(a, b);
          a = _mm256_sub_epi32(a, _mm256_and_si256(_mm256_cmpgt_epi32(a, m_mod_one), m_mod));
          _mm256_storeu_si256((__m256i *) (buf + j + k), a);
        }
      }
    }
  }
}


__attribute__((target("avx2")))
void superset_moebius_transform_simd(int *buf, int mod, int n) {
  assert((n & (n - 1)) == 0);
  auto m_zero = _mm256_set1_epi32(0);
  auto m_mod = _mm256_set1_epi32(mod);
  auto m_zero2 = _mm_set1_epi32(0);
  auto m_mod2 = _mm_set1_epi32(mod);
  for(int i = 1; i < n; i <<= 1) {
    for(int j = 0; j < n; j += i << 1) {
      if(i <= 2) {
        for(int k = 0; k < i; k++) {
          buf[j + k] += mod - buf[j + k + i];
          if(buf[j + k] >= mod) buf[j + k] -= mod;
        }
      } else if(i == 4) {
        for(int k = 0; k < i; k += 4) {
          auto a = _mm_loadu_si128((__m128i * )(buf + j + k));
          auto b = _mm_loadu_si128((__m128i * )(buf + j + k + i));
          a = _mm_sub_epi32(a, b);
          a = _mm_add_epi32(a, _mm_and_si128(_mm_cmpgt_epi32(m_zero2, a), m_mod2));
          _mm_storeu_si128((__m128i * )(buf + j + k), a);
        }
      } else {
        for(int k = 0; k < i; k += 8) {
          auto a = _mm256_loadu_si256((__m256i * )(buf + j + k));
          auto b = _mm256_loadu_si256((__m256i * )(buf + j + k + i));
          a = _mm256_sub_epi32(a, b);
          a = _mm256_add_epi32(a, _mm256_and_si256(_mm256_cmpgt_epi32(m_zero, a), m_mod));
          _mm256_storeu_si256((__m256i * )(buf + j + k), a);
        }
      }
    }
  }
}

template< int mod >
int *bitwise_and_convolution_simd(int *f, int *g, int n) {
  assert((n & (n - 1)) == 0);
  superset_zeta_transform_simd(f, mod, n);
  superset_zeta_transform_simd(g, mod, n);
  for(int i = 0; i < n; i++) f[i] = (1uLL * f[i] * g[i]) % mod;
  superset_moebius_transform_simd(f, mod, n);
  return f;
}

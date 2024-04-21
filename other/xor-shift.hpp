/**
 * @brief Xor-Shift
 * 
 */
struct XorShift {
private:
  constexpr static double R = 1.0 / 0xffffffff;
  uint64_t x;

public:
  explicit XorShift(uint64_t seed = 88172645463325252ull) : x(seed) {}

  template< typename T = uint64_t >
  inline T get() { // [0, 2^64)
    x ^= x << 7ull;
    x ^= x >> 9ull;
    return x;
  }

  inline uint32_t get(uint32_t r) { // [0, r)
    return ((uint64_t) get< uint32_t >() * r) >> 32ull;
  }

  inline uint32_t get(uint32_t l, uint32_t r) { // [l, r)
    return l + get(r - l);
  }

  inline double probability() { // [0.0, 1.0]
    return get< uint32_t >() * R;
  }
};

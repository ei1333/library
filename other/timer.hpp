/**
 * @brief Timer(タイマー)
 * 
 */
constexpr uint64_t CYCLES_PER_SEC = 3000000000; // AtCoder
// constexpr uint64_t CYCLES_PER_SEC = 3600000000; // Codeforces
// constexpr uint64_t CYCLES_PER_SEC = 2300000000; // yukicoder
struct Timer {
  uint64_t start;

  Timer() : start{} { reset(); }

  void reset() { start = get_cycle(); }

  inline double get_second() const { return (double) get_cycle() / CYCLES_PER_SEC; }

  inline uint64_t get_cycle() const {
    unsigned low, high;
    __asm__ volatile ("rdtsc" : "=a" (low), "=d" (high));
    return (((uint64_t) low) | ((uint64_t) high << 32ull)) - start;
  }
};

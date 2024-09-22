#include "../math/combinatorics/modint-61-1.hpp"

template <typename T = char>
struct RollingHash {
 private:
  using mint = ModInt61_1;

  static mint generate_base() {
    mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<uint64_t> rand(1, mint::mod() - 1);
    return mint(rand(mt));
  }

  static mint base, base_inv;
  static vector<mint> bases, base_invs;

  vector<T> pre, suf;
  vector<mint> PRE{mint(0)}, SUF{mint(0)};

  static void expand_bases(size_t n) {
    if (bases.size() < n + 1) {
      int pre_sz = (int)bases.size();
      bases.resize(n + 1);
      for (int i = pre_sz - 1; i < n; i++) {
        bases[i + 1] = bases[i] * base;
      }
    }
  }

  static void expand_base_invs(size_t n) {
    if (base_invs.size() < n + 1) {
      int pre_sz = (int)base_invs.size();
      base_invs.resize(n + 1);
      for (int i = pre_sz - 1; i < n; i++) {
        base_invs[i + 1] = base_invs[i] * base_inv;
      }
    }
  }

 public:
  RollingHash() = default;

  explicit RollingHash(const string& s) {
    for (auto& c : s) push_back(c);
  }

  explicit RollingHash(const vector<T>& s) {
    for (auto& c : s) push_back(c);
  }

  int size() const { return (int)pre.size() + (int)suf.size(); }

  void push_front(T c) {
    expand_base_invs(pre.size() + 1);
    PRE.push_back(PRE.back() + base_invs[pre.size() + 1] * mint(c));
    pre.push_back(c);
  }

  void push_back(T c) {
    expand_bases(suf.size());
    SUF.push_back(SUF.back() + bases[suf.size()] * mint(c));
    suf.push_back(c);
  }

  T operator[](int k) const {
    assert(0 <= k and k < size());
    k -= (int)pre.size();
    return k < 0 ? pre[~k] : suf[k];
  }

  mint get(int r) const {
    assert(0 <= r and r <= size());
    r -= (int)pre.size();
    expand_bases(pre.size());
    if (r < 0) {
      return bases[pre.size()] * (PRE.back() - PRE[-r]);
    } else {
      return bases[pre.size()] * (PRE.back() + SUF[r]);
    }
  }

  mint get(int l, int r) const {
    assert(0 <= l and l <= r and r <= size());
    expand_base_invs(l);
    return base_invs[l] * (get(r) - get(l));
  }

  int lcp(const RollingHash& b) const {
    int len = min(size(), b.size());
    int low = 0, high = len + 1;
    while (high - low > 1) {
      int mid = (low + high) / 2;
      if (get(mid) == b.get(mid))
        low = mid;
      else
        high = mid;
    }
    return low;
  }

  void clear() {
    pre.clear();
    pre.shrink_to_fit();
    suf.clear();
    suf.shrink_to_fit();
    PRE = {mint(1)};
    PRE.shrink_to_fit();
    SUF = {mint(1)};
    SUF.shrink_to_fit();
  }

  void merge(RollingHash& b) {
    if (size() < b.size()) {
      pre.swap(b.pre);
      suf.swap(b.suf);
      PRE.swap(b.PRE);
      SUF.swap(b.SUF);
      reverse(b.suf.begin(), b.suf.end());
      for (auto& c : b.suf) push_front(c);
      for (auto& c : b.pre) push_front(c);
    } else {
      reverse(b.pre.begin(), b.pre.end());
      for (auto& c : b.pre) push_back(c);
      for (auto& c : b.suf) push_back(c);
    }
    b.clear();
  }
};

template <typename T>
ModInt61_1 RollingHash<T>::base = RollingHash::generate_base();
template <typename T>
ModInt61_1 RollingHash<T>::base_inv = base.inv();
template <typename T>
vector<ModInt61_1> RollingHash<T>::bases = {ModInt61_1(1)};
template <typename T>
vector<ModInt61_1> RollingHash<T>::base_invs = {ModInt61_1(1)};

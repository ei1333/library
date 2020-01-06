#define IGNORE

template< int mod >
struct ModInt {
  int x;
 
  ModInt() : x(0) {}
 
  ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
 
  ModInt &operator+=(const ModInt &p) {
    if((x += p.x) >= mod) x -= mod;
    return *this;
  }
 
  ModInt &operator-=(const ModInt &p) {
    if((x += mod - p.x) >= mod) x -= mod;
    return *this;
  }
 
  ModInt &operator*=(const ModInt &p) {
    x = (int) (1LL * x * p.x % mod);
    return *this;
  }
 
  ModInt &operator/=(const ModInt &p) {
    *this *= p.inverse();
    return *this;
  }
 
  ModInt operator-() const { return ModInt(-x); }
 
  ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
 
  ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
 
  ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
 
  ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }
 
  bool operator==(const ModInt &p) const { return x == p.x; }
 
  bool operator!=(const ModInt &p) const { return x != p.x; }
 
  ModInt inverse() const {
    int a = x, b = mod, u = 1, v = 0, t;
    while(b > 0) {
      t = a / b;
      swap(a -= t * b, b);
      swap(u -= t * v, v);
    }
    return ModInt(u);
  }
 
  ModInt pow(int64_t n) const {
    ModInt ret(1), mul(x);
    while(n > 0) {
      if(n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }
 
  friend ostream &operator<<(ostream &os, const ModInt &p) {
    return os << p.x;
  }
 
  friend istream &operator>>(istream &is, ModInt &a) {
    int64_t t;
    is >> t;
    a = ModInt< mod >(t);
    return (is);
  }
};
 
using modint = ModInt< mod >;
 
template< typename T >
struct Combination {
  vector< T > _fact, _rfact;
 
  Combination(int sz) : _fact(sz + 1), _rfact(sz + 1) {
    _fact[0] = _rfact[sz] = 1;
    for(int i = 1; i <= sz; i++) _fact[i] = _fact[i - 1] * i;
    _rfact[sz] /= _fact[sz];
    for(int i = sz - 1; i >= 0; i--) _rfact[i] = _rfact[i + 1] * (i + 1);
  }
 
  inline T fact(int k) const { return _fact[k]; }
 
  inline T rfact(int k) const { return _rfact[k]; }
 
  T P(int n, int r) const {
    if(r < 0 || n < r) return 0;
    return fact(n) * rfact(n - r);
  }
 
  T C(int p, int q) const {
    if(q < 0 || p < q) return 0;
    return fact(p) * rfact(q) * rfact(p - q);
  }
 
  T H(int n, int r) const {
    if(n < 0 || r < 0) return (0);
    return r == 0 ? 1 : C(n + r - 1, r);
  }
};
 
int64_t euler_phi(int64_t n) {
  int64_t ret = n;
  for(int64_t i = 2; i * i <= n; i++) {
    if(n % i == 0) {
      ret -= ret / i;
      while(n % i == 0) n /= i;
    }
  }
  if(n > 1) ret -= ret / n;
  return ret;
}
 
int main() {
  int N, M, K;
  cin >> N >> M >> K;
  UnWeightedGraph g(N);
  Combination< modint > beet(101010);
  while(M--) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  BiConnectedComponents< UnWeightedGraph > bcc(g);
  bcc.build();
  modint ret = 1;
  for(auto &vs : bcc.bc) {
    set< int > vertex;
    for(auto &p : vs) vertex.emplace(p.first);
    for(auto &p : vs) vertex.emplace(p.second);
    if(vertex.size() == vs.size() + 1) {
      ret *= K;
    } else if(vertex.size() == vs.size()) {
      modint add = 0;
      for(int i = 1; i <= vertex.size(); i++) {
        if(vertex.size() % i == 0) {
          add += modint(K).pow(vertex.size() / i) * euler_phi(i);
        }
      }
      add /= vertex.size();
      ret *= add;
    } else {
      ret *= beet.H(K, vs.size());
    }
  }
  cout << ret << endl;
}

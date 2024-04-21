// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/705

#include "../../template/template.hpp"

#include "../../dp/online-offline-dp.hpp"

int main() {
  int n;
  cin >> n;
  vector< int > a(n), x(n), y(n);
  for(int i = 0; i < n; i++) cin >> a[i];
  for(int i = 0; i < n; i++) cin >> x[i];
  for(int i = 0; i < n; i++) cin >> y[i];
  function< int64_t(int, int) > dist = [&](int i, int j) {
    assert(0 <= i && i < j && j <= n);
    int s = abs(a[j - 1] - x[i]);
    int t = abs(y[i]);
    return 1LL * s * s * s + 1LL * t * t * t;
  };
  cout << online_offline_dp(n, dist).back() << endl;
}

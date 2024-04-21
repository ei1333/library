// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1549

#include "../../template/template.hpp"

#include "../../structure/wavelet/succinct-indexable-dictionary.hpp"
#include "../../structure/wavelet/wavelet-tree.hpp"

int main() {
  int n;
  cin >> n;

  const int OFS = 1e6;
  vector< int > as(n);
  for(int i = 0; i < n; i++) cin >> as[i], as[i] += OFS;
  CompressedWaveletTree< int, 17 > wm(as);

  int q;
  cin >> q;
  for(int i = 0; i < q; i++) {
    int l, r, d;
    cin >> l >> r >> d;
    r++;
    d += OFS;
    int ans = OFS * 2;
    if(wm.rank(d, l) < wm.rank(d, r)) {
      ans = 0;
    } else {
      int succ = wm.next_value(l, r, d);
      if(~succ) chmin(ans, abs(succ - d));
      int pred = wm.prev_value(l, r, d);
      if(~pred) chmin(ans, abs(pred - d));
    }
    cout << ans << "\n";
  }
}

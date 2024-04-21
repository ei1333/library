// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0560

#include "../../template/template.hpp"

#include "../../dp/cumulative-sum-2d.hpp"


int main() {
  int N, M, Q;
  cin >> N >> M >> Q;
  vector< CumulativeSum2D< int > > sum(3, CumulativeSum2D< int >(N, M));
  const string P = "JOI";
  for(int i = 0; i < N; i++) {
    string s;
    cin >> s;
    for(int j = 0; j < M; j++) {
      for(int k = 0; k < 3; k++) {
        sum[k].add(i, j, s[j] == P[k]);
      }
    }
  }
  for(int k = 0; k < 3; k++) {
    sum[k].build();
  }
  while(Q--) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    --a, --b;
    vector< int > v(3);
    for(int k = 0; k < 3; k++) {
      v[k] = sum[k].query(a, b, c, d);
    }
    cout << v << "\n";
  }

}

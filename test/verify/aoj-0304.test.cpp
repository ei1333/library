// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0304

#include "../../template/template.hpp"

#include "../../graph/shortest-path/bellman-ford.hpp"

int main() {
  int N, C;
  int A[200], O[200], B[200], S[200], D[200];

  cin >> N >> C;
  vector< int > undefined;
  for(int i = 0; i < C; i++) {
    string str;
    cin >> str;
    int tail = 0, a = 0, b = 0, o, s, d = 0;
    while(isdigit(str[tail])) a = a * 10 + str[tail++] - '0';
    if(str[tail] == '*') o = 2;
    else if(str[tail] == '<') o = 0, ++tail;
    else o = 1, ++tail;
    ++tail;
    while(isdigit(str[tail])) b = b * 10 + str[tail++] - '0';
    if(str[tail] == '+') s = 0;
    else s = 1;
    ++tail;
    while(tail < str.size()) d = d * 10 + str[tail++] - '0';
    A[i] = --a, B[i] = --b, O[i] = o, S[i] = s, D[i] = d;
    if(o == 2) undefined.push_back(i);
  }
  int ret = -1;
  for(int i = 0; i < (1 << undefined.size()); i++) {
    for(int j = 0; j < undefined.size(); j++) O[undefined[j]] = (i >> j) & 1;

    Edges<> es;
    for(int k = 0; k < C; k++) {
      if(O[k] == 1) swap(A[k], B[k]);
      es.emplace_back(B[k], A[k], 0);
      if(S[k] == 0) es.emplace_back(B[k], A[k], -D[k]);
      else es.emplace_back(A[k], B[k], D[k]);
      if(O[k] == 1) swap(A[k], B[k]);
    }
    auto dists = bellman_ford(es, N, 0);
    if(dists.empty() || *min_element(begin(dists), end(dists)) < 0) continue;
    ret = max(ret, *max_element(begin(dists), end(dists)));
  }

  if(ret >= numeric_limits< int >::max()) cout << "inf" << endl;
  else cout << ret << endl;
}


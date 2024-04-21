// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2405

#include "../../template/template.hpp"
#include "../../math/combinatorics/mod-int.hpp"

#include "../../graph/others/tree-decomposition-width-2.hpp"

const int MOD = 1000003;
using Mint = ModInt< MOD >;

int main() {
  int N, M;
  while(cin >> N >> M, N) {
    TreeDecompositionWidth2 td(N);
    set< pair< int, int > > edges;
    for(int i = 0; i < N; i++) {
      td.add_edge(i, (i + 1) % N);
      edges.emplace(minmax(i, (i + 1) % N));
    }
    for(int i = 0; i < M; i++) {
      int a, b;
      cin >> a >> b;
      --a, --b;
      td.add_edge(a, b);
      edges.emplace(minmax(a, b));
    }

    if(N % 2) {
      cout << 0 << endl;
      continue;
    }

    auto t = td.build();
    to_nice(t);
    vector< vector< Mint > > dps(t.size());
    vector< int > buff(N), buff2(N, -1);
    MFP([&](auto rec, int idx) -> void {

      auto &ch = t[idx].child;
      auto &bag = t[idx].bag;

      for(auto &to : ch) rec(to);
      vector< Mint > dp(1 << bag.size());

      if(ch.empty()) { // leaf
        dp[0] = 1;
      } else if(ch.size() == 2) { // join
        for(int i = 0; i < dp.size(); i++) {
          for(int j = 0; j < dp.size(); j++) {
            if((i & j) == 0) dp[i | j] += dps[ch[0]][i] * dps[ch[1]][j];
          }
        }
      } else {
        auto &ch_bag = t[ch[0]].bag;
        auto &ch_dp = dps[ch[0]];

        for(int i = 0; i < bag.size(); i++) {
          buff[bag[i]] = 1 << i;
          buff2[bag[i]] = idx;
        }

        if(ch_bag.size() + 1 == bag.size()) { // introduce
          for(int i = 0; i < ch_dp.size(); i++) {
            int bit = 0;
            for(int j = 0; j < ch_bag.size(); j++) {
              if((i >> j) & 1) bit |= buff[ch_bag[j]];
            }
            dp[bit] = ch_dp[i];
          }
        } else { // forget
          int v = -1;
          for(int i = 0; i < ch_bag.size(); i++) {
            if(buff2[ch_bag[i]] != idx) v = ch_bag[i];
          }
          vector< int > ok_match(bag.size());
          for(int i = 0; i < bag.size(); i++) {
            ok_match[i] = edges.count(minmax(bag[i], v));
          }

          for(int i = 0; i < ch_dp.size(); i++) {
            int bit = 0;
            bool v_use = false;
            for(int j = 0; j < ch_bag.size(); j++) {
              if((i >> j) & 1) {
                if(v != ch_bag[j]) bit |= buff[ch_bag[j]];
              } else {
                if(v == ch_bag[j]) v_use = true;
              }
            }
            if(v_use) {
              for(int j = 0; j < bag.size(); j++) {
                if((bit >> j) & 1) continue;
                if(ok_match[j]) dp[bit | (1 << j)] += ch_dp[i];
              }
            } else {
              dp[bit] += ch_dp[i];
            }
          }
        }
      }
      dps[idx].swap(dp);
    })(0);
    auto &dp = dps[0];
    cout << dp.back() << endl;
  }
}


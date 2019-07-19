struct LongestCommonPrefixArray {
  const SuffixArray &SA;
  vector< int > LCP, rank;

  LongestCommonPrefixArray(const SuffixArray &SA) : SA(SA), LCP(SA.size()) {
    rank.resize(SA.size());
    for(int i = 0; i < SA.size(); i++) {
      rank[SA[i]] = i;
    }
    for(int i = 0, h = 0; i < SA.size(); i++) {
      if(rank[i] + 1 < SA.size()) {
        for(int j = SA[rank[i] + 1]; max(i, j) + h < SA.size() && SA.s[i + h] == SA.s[j + h]; ++h);
        LCP[rank[i] + 1] = h;
        if(h > 0) --h;
      }
    }
  }

  int operator[](int k) const {
    return LCP[k];
  }

  size_t size() const {
    return LCP.size();
  }

  void output() {
    for(int i = 0; i < size(); i++) {
      cout << i << ": " << LCP[i] << " " << SA.s.substr(SA[i]) << endl;
    }
  }
};

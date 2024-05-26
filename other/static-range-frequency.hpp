template <typename T>
struct StaticRangeFrequency {
 private:
  vector<T> vs;
  vector<vector<int> > mp;

 public:
  explicit StaticRangeFrequency(const vector<T> &xs) : vs{xs} {
    sort(vs.begin(), vs.end());
    vs.erase(unique(vs.begin(), vs.end()), vs.end());
    mp.resize(vs.size());
    for (int i = 0; i < xs.size(); i++) {
      int p = lower_bound(vs.begin(), vs.end(), xs[i]) - vs.begin();
      mp[p].emplace_back(i);
    }
  }
  size_t query(int l, int r, T x) const {
    int p = lower_bound(vs.begin(), vs.end(), x) - vs.begin();
    if (p == vs.size() or x != vs[p]) return 0;
    l = lower_bound(mp[p].begin(), mp[p].end(), l) - vs.begin();
    r = lower_bound(mp[p].begin(), mp[p].end(), r) - vs.begin();
    return r - l;
  }
};

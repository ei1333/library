/**
 * @brief Suffix Array(接尾辞配列)
 */
template< typename T >
struct SuffixArray : vector< int > {
private:
  vector< int > sa_is(const vector< int > &s) const {
    const int n = (int) s.size();
    vector< int > ret(n);

    vector< int > is_s(n), is_lms(n);
    int m = 0;
    for(int i = n - 2; i >= 0; i--) {
      is_s[i] = (s[i] > s[i + 1]) or (s[i] == s[i + 1] and is_s[i + 1]);
      m += (is_lms[i + 1] = is_s[i] and not is_s[i + 1]);
    }

    auto induced_sort = [&](const vector< int > &lms) {
      int upper = *max_element(s.begin(), s.end());
      vector< int > l(upper + 2), r(upper + 2);
      for(auto &&v: s) {
        ++l[v + 1];
        ++r[v];
      }
      partial_sum(l.begin(), l.end(), l.begin());
      partial_sum(r.begin(), r.end(), r.begin());
      fill(ret.begin(), ret.end(), -1);
      for(int i = (int) lms.size() - 1; i >= 0; i--) {
        ret[--r[s[lms[i]]]] = lms[i];
      }
      for(auto &&v: ret) {
        if(v >= 1 and is_s[v - 1]) ret[l[s[v - 1]]++] = v - 1;
      }
      fill(r.begin(), r.end(), 0);
      for(auto &&v: s) ++r[v];
      partial_sum(r.begin(), r.end(), r.begin());
      for(int k = (int) ret.size() - 1, i = ret[k]; k >= 1; i = ret[--k]) {
        if(i >= 1 and not is_s[i - 1]) {
          ret[--r[s[i - 1]]] = i - 1;
        }
      }
    };

    vector< int > lms;
    lms.reserve(m);
    for(int i = 1; i < n; i++) {
      if(is_lms[i]) lms.push_back(i);
    }

    induced_sort(lms);

    vector< int > new_lms;
    new_lms.reserve(m);
    for(int i = 0; i < n; i++) {
      if(not is_s[ret[i]] and ret[i] > 0 and is_s[ret[i] - 1]) {
        new_lms.push_back(ret[i]);
      }
    }

    auto is_same = [&](int a, int b) {
      if(s[a++] != s[b++]) return false;
      for(;; ++a, ++b) {
        if(s[a] != s[b]) return false;
        if(is_lms[a] or is_lms[b]) return is_lms[a] and is_lms[b];
      }
    };

    int rank = 0;
    ret[n - 1] = 0;
    for(int i = 1; i < m; i++) {
      if(not is_same(new_lms[i - 1], new_lms[i])) ++rank;
      ret[new_lms[i]] = rank;
    }

    if(rank + 1 < m) {
      vector< int > new_s(m);
      for(int i = 0; i < m; i++) {
        new_s[i] = ret[lms[i]];
      }
      auto lms_sa = sa_is(new_s);
      for(int i = 0; i < m; i++) {
        new_lms[i] = lms[lms_sa[i]];
      }
    }

    induced_sort(new_lms);

    return ret;
  }

public:
  T vs;

  explicit SuffixArray(const T &vs, bool compress = false) : vs(vs) {
    vector< int > new_vs(vs.size() + 1);
    if(compress) {
      T xs = vs;
      sort(xs.begin(), xs.end());
      xs.erase(unique(xs.begin(), xs.end()), xs.end());
      for(int i = 0; i < (int) vs.size(); i++) {
        new_vs[i] = std::lower_bound(xs.begin(), xs.end(), vs[i]) - xs.begin() + 1;
      }
    } else {
      auto d = *min_element(vs.begin(), vs.end());
      for(int i = 0; i < (int) vs.size(); i++) {
        new_vs[i] = vs[i] - d + 1;
      }
    }
    auto ret = sa_is(new_vs);
    assign(ret.begin(), ret.end());
  }

  void output() const {
    for(int i = 0; i < size(); i++) {
      cout << i << ":[" << (*this)[i] << "]";
      for(int j = (*this)[i]; j < (int) vs.size(); j++) cout << " " << vs[j];
      cout << "\n";
    }
  }


  bool lt_substr(const string &t, int si = 0, int ti = 0) {
    int sn = (int) vs.size(), tn = (int) t.size();
    while(si < sn && ti < tn) {
      if(vs[si] < t[ti]) return true;
      if(vs[si] > t[ti]) return false;
      ++si, ++ti;
    }
    return si >= sn && ti < tn;
  }

  // t <= s[i,N) なる最小の i を返す O(|t| log |s|)
  int lower_bound(const T &t) {
    int ng = 0, ok = (int) size();
    while(ok - ng > 1) {
      int mid = (ok + ng) / 2;
      if(lt_substr(t, at(mid))) ng = mid;
      else ok = mid;
    }
    return ok;
  }

  // O(|t| log |s|)
  pair< int, int > equal_range(T &t) {
    int low = lower_bound(t);
    int ng = low - 1, ok = (int) size();
    t.back()++;
    while(ok - ng > 1) {
      int mid = (ok + ng) / 2;
      if(lt_substr(t, at(mid))) ng = mid;
      else ok = mid;
    }
    t.back()--;
    return {low, ok};
  }
};

template<>
void SuffixArray< string >::output() const {
  for(int i = 0; i < (int) size(); i++) {
    cout << i << ":[" << (*this)[i] << "] " << vs.substr((*this)[i]) << "\n";
  }
}

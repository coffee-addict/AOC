#include <bits/stdc++.h>
using namespace std;

#define FOR(i,s,e) for(int i=(s);(i)<(int)(e);++(i))
#define REP(i,e) FOR(i,0,e)
#define all(o) (o).begin(), (o).end()
#define epb(x) emplace_back((x))
#define psb(x) push_back((x))
#define ppb(x) pop_back((x))
#define mkp(x,y) make_pair((x),(y))
#define mkt(x,y,z) make_tuple((x),(y),(z))
#define nth(x,n) get<(n)>((x))

using ll = long long;
using VI = vector<int>;
using VVI = vector<VI>;
using VL = vector<ll>;
using VVL = vector<VL>;
using VD = vector<double>;
using VLD = vector<long double>;

template<typename T>
struct edge {
  int from;
  int to;
  T cost;
  edge(int from, int to, T cost) {
    this->from = from;
    this->to = to;
    this->cost = cost;
  }
};
using VVE = vector<vector<edge<int>>>;

int encode(char c) {
  return (int)(c-'A');
}

const int L = 26;

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  string s; cin >> s; 
  int n; cin >> n; 
  vector<char> a(n), b(n), x(n);
  REP(i,n) {
    string ab; cin >> ab; 
    a[i] = ab[0];
    b[i] = ab[1];
    cin >> x[i];
  }
  VL res(L*L);
  REP(i,s.size()-1) {
    int j = encode(s[i])*L + encode(s[i+1]);
    res[j]++;
  }
  REP(xxx,40) {
    VL tmp = res;
    REP(i,n) {
      int jl = encode(a[i]), jr = encode(b[i]), jx = encode(x[i]);
      int j = jl*L + jr;
      ll c = res[j];
      if (c == 0) continue;
      int l = jl*L + jx, r = jx*L + jr;
      tmp[l] += c;
      tmp[r] += c;
      tmp[j] -= c;
    }
    res = tmp;
  }
  VL cnt(L);
  REP(i,L*L) {
    int il = i/L, ir = i%L;
    cnt[il] += res[i];
    cnt[ir] += res[i];
  }
  int i0 = encode(s[0]), ie = encode(s[s.size()-1]);
  if (cnt[i0]) cnt[i0]++;
  if (cnt[ie]) cnt[ie]++;
  ll c0 = LLONG_MAX, c1 = 0;
  REP(i,L) if (cnt[i]) {
    c0 = min(c0, cnt[i]/2);
    c1 = max(c1, cnt[i]/2);
  }
  cout << c1 - c0 << endl; 
  return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define FOR(i,s,e) for(int i=(s);(i)<(int)(e);++(i))
#define REP(i,e) FOR(i,0,e)
#define all(o) (o).begin(), (o).end()
#define epb(x) emplace_back((x))
#define psb(x) push_back((x))
#define ppb(x) pop_back((x))
#define mkp(x,y) make_pair((x),(y))
#define mkt(x,y) make_tuple((x),(y))
#define nth(x,n) get<(n)>((x))

using ll = long long;
using VI = vector<int>;
using VVI = vector<VI>;
using VL = vector<ll>;
using VVL = vector<VL>;
using VD = vector<double>;
using VLD = vector<long double>;
using TII = tuple<int,int>;

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

VI c2b(char c) {
  int d = (int)(c - '0');
  if (c == 'A')
    d = 10;
  else if (c == 'B')
    d = 11;
  else if (c == 'C')
    d = 12;
  else if (c == 'D')
    d = 13;
  else if (c == 'E')
    d = 14;
  else if (c == 'F')
    d = 15;
  VI res;
  while (d) {
    res.epb(d%2);
    d >>= 1;
  }
  int r = 4 - res.size();
  REP(i,r) res.epb(0);
  reverse(all(res));
  return res;
}

int parse_len_type_id(VI &d, int &p) {
  int res = d[p++];
  return res;
}

TII parse_header(VI &d, int &p) {
  int vs = 0;
  REP(i,3) {
    vs <<= 1;
    if (d[p+i]) vs++;
  }
  p += 3;
  int tp = 0;
  REP(i,3) {
    tp <<= 1;
    if (d[p+i]) tp++;
  }
  p += 3;
  return mkt(vs,tp);
}

int parse_fix_len(VI &d, int &p, int len) {
  int res = 0;
  REP(i,len) {
    res <<= 1;
    res += d[p++];
  }
  return res;
}

int parse_literal(VI &d, int &p) {
  VI v;
  int done = 0;
  while (done == 0) {
    if (d[p++] == 0) done = 1;
    REP(i,4) v.epb(d[p++]);
  }
  int res = 0;
  REP(i,v.size()) {
    res <<= 1;
    res += v[i];
  }
  return res;
}

TII parse(VI &d, int &p, int &cnt) {
cnt++;
  int res_vs = 0, res_lv = 0;
  int e = (int)d.size();
  // exceed the end or extra 0's: halt
  while (1) {
//    if (e - p + 1 < 6) break;
    if (e - p < 6) break;
    int vs0, tp0;
    tie(vs0,tp0) = parse_header(d, p);
cout << "version = " << vs0 << ", type = " << tp0 << ", at pos = " << p << endl;
if (e <= p) break;
    res_vs += vs0;
    if (tp0 == 4) {
      int lv1 = parse_literal(d, p);
      res_lv += lv1;
cout << "lit val = " << lv1 << endl;
    } else {
      int lti = parse_len_type_id(d, p);
      if (lti == 0) {
        if (e - p < 15) break;
        int hl = parse_fix_len(d, p, 15);
        int vs1 = 0, lv1 = 0;
        VI d1; REP(i,hl) d1.epb(d[p+i]);
        int p1 = 0;
        tie(vs1, lv1) = parse(d1, p1, cnt);
        res_vs += vs1;
        res_lv += lv1; 
cout << "op(hL): vs1 = " << vs1 << ", lv1 = " << lv1 
<< ", res_vs = " << res_vs << ", res_lv = " << res_lv << endl;
        // adjust position
        p += hl;
      } else {
        if (e - p < 11) break;
        int hm = parse_fix_len(d, p, 11);
        int vs1 = 0, lv1 = 0;
        REP(i,hm) {
          int vs2 = 0, lv2 = 0;
          tie(vs2, lv2) = parse(d, p, cnt);
          vs1 += vs2;
          lv1 += lv2;
        }
        res_vs += vs1;
        res_lv += lv1;
cout << "op(hM): vs1 = " << vs1 << ", lv1 = " << lv1 
<< ", res_vs = " << res_vs << ", res_lv = " << res_lv << endl;
      }
    }
  }
  return mkt(res_vs, res_lv);
}

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  int n; cin >> n; 
  REP(ni,n) {
    cout << "case " << ni+1 << ":\n";
    VI d;
    string s; cin >> s; 
    int m = (int)s.size();
    REP(i,m) {
      VI a = c2b(s[i]);
      REP(j,a.size()) d.epb(a[j]);
    }
    int vs, lv;
    int p = 0;
    int c = 0;
    cout << "len(d) = " << d.size() << endl;
    tie(vs, lv) = parse(d, p, c);
    cout << "cnt = " << c << endl;
    cout << "sum(versions) = " << vs << endl;
    cout << "sum(literal values) = " << lv << endl;
    cout << endl; 
  }
  return 0;
}

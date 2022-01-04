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

VL c2b(char c) {
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
  VL res;
  while (d) {
    res.epb(d%2);
    d >>= 1;
  }
  int r = 4 - res.size();
  REP(i,r) res.epb(0);
  reverse(all(res));
  return res;
}

int parse_len_type_id(VL &d, int &p) {
  int res = d[p++];
  return res;
}

TII parse_header(VL &d, int &p) {
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

int parse_fix_len(VL &d, int &p, int len) {
  int res = 0;
  REP(i,len) {
    res <<= 1;
    res += d[p++];
  }
  return res;
}

ll parse_literal(VL &d, int &p) {
  VL v;
  int done = 0;
  while (done == 0) {
    if (d[p++] == 0) done = 1;
    REP(i,4) v.epb(d[p++]);
  }
  ll res = 0;
  REP(i,v.size()) {
    res <<= 1;
    res += v[i];
  }
  return res;
}

ll op(int tp, VL v, int n) {
//cout << "tp = " << tp << ", v.size = " << v.size() << endl;
  ll res = v[0];
  if (tp == 0)
    FOR(i,1,n) res += v[i];
  else if (tp == 1)
    FOR(i,1,n) res *= v[i];
  else if (tp == 2)
    FOR(i,1,n) res = min(res, v[i]);
  else if (tp == 3)
    FOR(i,1,n) res = max(res, v[i]);
  else if (tp == 5)
    res = v[0] > v[1] ? 1 : 0;
  else if (tp == 6)
    res = v[0] < v[1] ? 1 : 0;
  else if (tp == 7)
    res = v[0] == v[1] ? 1 : 0;
  return res;
}

VL parse(VL &d, int &p, int &cnt) {
cnt++;
  VL res_lv;
  int e = (int)d.size();
  // exceed the end or extra 0's: halt
  while (1) {
    if (e - p < 6) break;
    int vs0, tp0;
    tie(vs0,tp0) = parse_header(d, p);
    if (e <= p) break;
    if (tp0 == 4) {
      res_lv.epb(parse_literal(d, p));
    } else {
      int lti = parse_len_type_id(d, p);
      if (lti == 0) {
        if (e - p < 15) break;
        int hl = parse_fix_len(d, p, 15);
        VL d1; REP(i,hl) d1.epb(d[p+i]);
        int p1 = 0;
        VL lv1 = parse(d1, p1, cnt);
//cout << "HL: type = " << tp0 << ", p = " << p << ", len(d) = " << d.size()
//<< ", lv1.size() = " << lv1.size() << endl;
//cout << "data to be processed: ";
//REP(i,lv1.size()) cout << lv1[i] << ' ';
//cout << endl; 
        res_lv.epb(op(tp0, lv1, lv1.size()));
        // adjust position
        p += hl;
      } else {
        if (e - p < 11) break;
        int hm = parse_fix_len(d, p, 11);
        VL lv1;
        REP(i,hm) {
          VL lv2 = parse(d, p, cnt);
          REP(j,lv2.size()) lv1.epb(lv2[j]);
        }
//cout << "HM = :" << hm << ", type = " << tp0 << ", p = " << p << ", len(d) = " << d.size()
//<< ", lv1.size() = " << lv1.size() << endl;
//cout << "data to be processed: ";
//REP(i,lv1.size()) cout << lv1[i] << ' ';
//cout << endl; 
        res_lv.epb(op(tp0, lv1, hm));
        FOR(i,hm,lv1.size()) res_lv.epb(lv1[i]);
      }
    }
  }
  return res_lv;
}

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  int n; cin >> n; 
  REP(ni,n) {
    cout << "case " << ni+1 << ":\n";
    VL d;
    string s; cin >> s; 
    int m = (int)s.size();
    REP(i,m) {
      VL a = c2b(s[i]);
      REP(j,a.size()) d.epb(a[j]);
    }
    int p = 0, c = 0;
    VL lv = parse(d, p, c);
    cout << "len(d) = " << d.size() << endl;
    cout << "cnt = " << c << endl;
    cout << "sum(literal values) = " << lv[0] << endl;
    cout << endl; 
  }
  return 0;
}

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

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  map<string,int> dc;
  dc["abcefg"] = 0;
  dc["cf"] = 1;
  dc["acdeg"] = 2;
  dc["acdfg"] = 3;
  dc["bcdf"] = 4;
  dc["abdfg"] = 5;
  dc["abdefg"] = 6;
  dc["acf"] = 7;
  dc["abcdefg"] = 8;
  dc["abcdfg"] = 9;
  int d = 10;
  int m = 4;
  int n; cin >> n; 
  int res = 0;
  REP(i,n) {
    VI c(7);
    VI p(7, -1), r(7, -1);
    vector<string> s(d);
    REP(j,d) cin >> s[j];
    REP(j,d) REP(k,s[j].size()) c[(int)(s[j][k]-'a')]++;
    int j1 = 0, j4 = 0, j7 = 0, j8 = 0;
    REP(j,d) {
      if (s[j].size() == 2) j1 = j;
      if (s[j].size() == 4) j4 = j;
      if (s[j].size() == 3) j7 = j;
      if (s[j].size() == 7) j8 = j;
    }

    // check 1(2)
    int k = (int)s[j1][0] - 'a';
    int l = (int)s[j1][1] - 'a';
    if (c[k] == 8) {
      p[(int)'c'-'a'] = k; // c -> ?
      p[(int)'f'-'a'] = l; // f -> ?
    } else {
      p[(int)'c'-'a'] = l; // f -> ?
      p[(int)'f'-'a'] = k; // c -> ?
    }

    // check 4(4)
    int pos_b = 0, pos_d = 0;
    REP(k,s[j4].size()) {
      if (c[(int)s[j4][k]-'a'] == 6) pos_b = k;
      if (c[(int)s[j4][k]-'a'] == 7) pos_d = k;
    }
    p[(int)'b'-'a'] = (int)s[j4][pos_b]-'a'; // b -> ?
    p[(int)'d'-'a'] = (int)s[j4][pos_d]-'a'; // d -> ?

    // check 7(3)
    REP(k,s[j7].size()) {
      int l = (int)s[j7][k]-'a';
      if (c[l] != 8) continue;
      if (l == p[(int)'c'-'a']) continue;
      p[(int)'a'-'a'] = l;
    }

    // check 8(7)
    int pos_e = 0;
    REP(k,s[j8].size()) {
      if (c[(int)s[j8][k]-'a'] == 4) pos_e = k;
    }
    p[(int)'e'-'a'] = (int)s[j8][pos_e]-'a'; // e -> ?
    // look for g
    int id_g = 0;
    REP(j,7) {
      int found = 0;
      REP(k,7) if (j == p[k]) found = 1;
      if (found == 0) id_g = j;
    }
    p[(int)'g'-'a'] = id_g;

    REP(j,7) r[p[j]] = j;

//cout << "c:\n";
//REP(j,7) cout <<  c[j] << ' ';
//cout << endl; 
//
//cout << "p:\n";
//REP(j,7) cout <<  p[j] << ' ';
//cout << endl; 
//
//cout << "r:\n";
//REP(j,7) cout <<  r[j] << ' ';
//cout << endl; 
    int x = 0;
    REP(j,m) {
      x *= 10;
      string t; cin >> t;
      sort(all(t));
      // decode
      string u;
      REP(k,t.size()) u += (char)('a' + r[(int)t[k]-'a']);
//cout << "t, u = "  << t << ", " << u << endl;
      sort(all(u));
      x += dc[u];
    }
//cout << "i, x = " << i << ", " << x << endl;
    res += x;
  }
  cout << res << endl; 
  return 0;
}

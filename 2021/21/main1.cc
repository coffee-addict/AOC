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
  int pa, pb; cin >> pa >> pb; 
  pa--; pb--;
  int sa = 0, sb = 0;
  int v = 1;
  int c = 0, ws = 0, ls = 0;
  while (ws < 1000) {
    REP(i,3) {
      pa += v;
      v++;
      if (v > 100) v = 1;
    }
    c += 3;
    pa = pa%10;
    sa += pa + 1;
    if (sa >= 1000) {
      ws = sa;
      ls = sb;
      break;
    } 
    REP(i,3) {
      pb += v;
      v++;
      if (v > 100) v = 1;
    }
    c += 3;
    pb = pb%10;
    sb += pb + 1;
    if (sb >= 1000) {
      ws = sb;
      ls = sa;
      break;
    } 
  }
  cout << "c, ws, ls = " << c << ", " << ws << ", " << ls << endl;
  cout << ls*c << endl;
  return 0;
}

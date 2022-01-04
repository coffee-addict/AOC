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

const int H = 2000;
const int W = 2000;

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  int cases; cin >> cases; 
  REP(cc,cases) {
    int n; cin >> n; 
    VVI b(H, VI(W));
    REP(i,n) {
      int x, y; cin >> x >> y;
      b[y][x] = 1;
    }
    int ci; cin >> ci;
    REP(cci,ci) {
      string xy; cin >> xy; 
      int p; cin >> p; 
      if (xy == "x") {
        REP(i,H) FOR(j,p+1,p*2+1) {
          if (p*2-j < 0) continue;
          if (b[i][j] == 0) continue;
          b[i][p*2-j] = b[i][j];
          b[i][j] = 0;
        }
      } else {
        REP(j,W) FOR(i,p+1,p*2+1) {
          if (p*2-i < 0) continue;
          if (b[i][j] == 0) continue;
          b[p*2-i][j] = b[i][j];
          b[i][j] = 0;
        }
      }
    }
    int X = 0, Y = 0;
    REP(i,H) REP(j,W) {
      if (b[i][j]) {
        X = max(X, j);
        Y = max(Y, i);
      }
    }
    REP(i,30) {
      REP(j,70) {
        char o = b[i][j] ? '#' : '.';
        cout << o ;
      }
      cout << endl; 
    }
  }
  return 0;
}

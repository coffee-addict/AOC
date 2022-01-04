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
using VVVI = vector<VVI>;
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

  int h, w;
  cin >> h >> w;
  VVVI b(2, VVI(h, VI(w)));
  REP(i,h) {
    string s; cin >> s; 
    REP(j,w) {
      char c = s[j];
      if (c == '.') continue;
      b[0][i][j] = c=='>' ? 1 : 2;
    }
  }
  int res = 0;
  while (1) {
    res++;
    VVI b0(h, VI(w));
    REP(i,h) REP(j,w) b0[i][j] = b[0][i][j];
    REP(i,h) REP(j,w) {
      int c = b[0][i][j];
      if (c == 2)
        b[1][i][j] = c;
      else if (c == 1) {
        int ny = i, nx = (j+1)%w;
        if (b[0][ny][nx] == 0)
          b[1][ny][nx] = c;
        else
          b[1][i][j] = c;
      }
    }
    REP(i,h) REP(j,w) b[0][i][j] = b[1][i][j];
    REP(i,h) REP(j,w) b[1][i][j] = 0;
    REP(i,h) REP(j,w) {
      int c = b[0][i][j];
      if (c == 1)
        b[1][i][j] = b[0][i][j];
      else if (c == 2) {
        int ny = (i+1)%h, nx = j;
        if (b[0][ny][nx] == 0)
          b[1][ny][nx] = c;
        else
          b[1][i][j] = c;
      }
    }
    int done = 1;
    REP(i,h) REP(j,w) if (b0[i][j] != b[1][i][j]) done = 0;
    if (done) break;
    REP(i,h) REP(j,w) b[0][i][j] = b[1][i][j];
    REP(i,h) REP(j,w) b[1][i][j] = 0;
  }
  cout << res << endl; 
  return 0;
}

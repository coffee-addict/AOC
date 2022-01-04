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

ll dp[2][10][10][40][40];

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  int pa, pb; cin >> pa >> pb; 
  pa--; pb--;
  int r = 100;
  dp[0][pa][pb][0][0] = 1;
  int t = 0;
  ll w0 = 0, w1 = 0;
  while (r--) {
    REP(i,10) REP(j,10) REP(k,40) REP(l,40) dp[(t+1)&1][i][j][k][l] = 0;
    REP(pi,10) REP(pj,10) REP(si,40) REP(sj,40) {
      if (dp[t][pi][pj][si][sj] == 0) continue;
      if (si >= 21 || sj >= 21) continue;
      // 3^3 states
      REP(x0,3) REP(x1,3) REP(x2,3) {
        if (t == 0) {
          int npi = (pi + x0 + x1 + x2 + 3)%10;
          int nsi = si + npi + 1;
          dp[(t+1)&1][npi][pj][nsi][sj] += dp[t][pi][pj][si][sj];
          if (nsi >= 21) w0 += dp[t][pi][pj][si][sj];
        } else {
          int npj = (pj + x0 + x1 + x2 + 3)%10;
          int nsj = sj + npj + 1;
          dp[(t+1)&1][pi][npj][si][nsj] += dp[t][pi][pj][si][sj];
          if (nsj >= 21) w1 += dp[t][pi][pj][si][sj];
        }
      }
    }
    t = (t+1)&1;
  }
  cout << w0 << endl; 
  cout << w1 << endl; 
  return 0;
}


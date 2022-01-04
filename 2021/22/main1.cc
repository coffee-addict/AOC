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

const int N = 300;

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  int cases; cin >> cases; 
  VVVI c(N, VVI(N, VI(N)));
  VVI lr(N, VI(3)), ur(N, VI(3));
  VI s(N);
  REP(xxx,cases) {
    int n; cin >> n; 
    REP(i,n) {
      string ss; cin >> ss; 
      if (ss == "on") s[i] = 1;
      int lx, ux, ly, uy, lz, uz;
      cin >> lx >> ux >> ly >> uy >> lz >> uz; 
      lr[i][0] = lx; lr[i][1] = ly; lr[i][2] = lz;
      ur[i][0] = ux; ur[i][1] = uy; ur[i][2] = uz;
      if (ss == "on") {
        FOR(i,lx,ux+1) FOR(j,ly,uy+1) FOR(k,lz,uz+1) c[N/2+i][N/2+j][N/2+k] = 1;
      } else {
        FOR(i,lx,ux+1) FOR(j,ly,uy+1) FOR(k,lz,uz+1) c[N/2+i][N/2+j][N/2+k] = 0;
      }
    }
    int res = 0;
    REP(i,N) REP(j,N) REP(k,N) if (c[i][j][k]) res++;
    cout << res << endl; 
  }
  return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define FOR(i,s,e) for(int i=(s);(i)<(int)(e);++(i))
#define REP(i,e) FOR(i,0,e)
#define all(o) (o).begin(), (o).end()

#define epb(x) emplace_back((x))
#define psb(x) push_back((x))
#define ppb(x) pop_back((x))

using ll = long long;
using VI = vector<int>;
using VVI = vector<VI>;
using VL = vector<ll>;
using VVL = vector<VL>;
using VD = vector<double>;
using VLD = vector<long double>;

const int H = 5;
const int W = 5;

int win(VVL c) {
  REP(i,H) {
    int x = 0;
    REP(j,W) x += c[i][j];
    if (x == W) return 1;
  }
  REP(j,W) {
    int x = 0;
    REP(i,H) x += c[i][j];
    if (x == H) return 1;
  }
  return 0;
}

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  int n; cin >> n;
  VI x(n);
  REP(i,n) cin >> x[i];
  int nb; cin >> nb;
  VVL b[nb], c[nb];
  REP(i,nb) {
    b[i] = vector<vector<ll>>(H, vector<ll>(W));
    c[i] = vector<vector<ll>>(H, vector<ll>(W));
    REP(j,H) REP(k,W) cin >> b[i][j][k];
  }
  REP(i,n) {
    REP(j,nb) REP(k,H) REP(l,W) if (b[j][k][l] == x[i]) c[j][k][l] = 1;
    int done = 0;
    REP(j,nb) {
      if (win(c[j])) {
        ll y = 0;
        REP(k,H) REP(l,W) if (c[j][k][l] == 0) y += b[j][k][l];
        cout << y*x[i] << endl;
        done = 1;
      }
    }
    if (done) break;
  }
  return 0;
}

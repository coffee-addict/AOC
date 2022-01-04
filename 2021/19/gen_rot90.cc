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
using TIII = tuple<int,int,int>;

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

// return A*B
VVI prod_2mats(VVI A, VVI B) {
  VVI res(3, VI(3));
  REP(i,3) REP(j,3) {
    REP(k,3) res[i][j] += A[i][k]*B[k][j];
  }
  return res;
}

VVVI gen_rotmats() {
  VVI A = {
    {1, 0, 0},
    {0, 0, -1},
    {0, 1, 0},
  };
  VVI B = {
    {0, 0, 1},
    {0, 1, 0},
    {-1, 0, 0}
  };
  VVVI res;
  REP(p,4) REP(q,4) REP(r,4) REP(s,4) {
    VVI X(3, VI(3));
    REP(i,3) X[i][i] = 1;
    REP(t,s) X = prod_2mats(B, X);
    REP(t,r) X = prod_2mats(A, X);
    REP(t,q) X = prod_2mats(B, X);
    REP(t,p) X = prod_2mats(A, X);
    res.epb(X);
  }
  return res;
}

int main() {
  VVVI res = gen_rotmats();
  sort(all(res));
  res.erase(unique(all(res)), res.end());
  REP(i,res.size()) {
    REP(j,3) {
      REP(k,3) cout << res[i][j][k] << ' ';
      cout << endl; 
    }
  }
  return 0;
}


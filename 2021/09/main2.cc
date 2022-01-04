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

const int H = 100;
const int W = 100;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int h, w;
int p[H][W];
VVI b;

int dfs(int si, int sj) {
  p[si][sj] = 1;
  int res = 1;
  REP(i,4) {
    int ny = si + dy[i], nx = sj + dx[i];
    if (ny < 0 || h <= ny) continue;
    if (nx < 0 || w <= nx) continue;
    if (p[ny][nx]) continue;
    if (b[si][sj] < b[ny][nx]) res += dfs(ny, nx);
  }
  return res;
}

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  cin >> h;
  b.resize(h);
  REP(i,h) {
    string s; cin >> s;
    w = (int)s.size();
    b[i].resize(w);
    REP(j,w) b[i][j] = (int)(s[j] - '0');
  }
  VI v;
  memset(p, 0, sizeof(p));
  REP(i,h) REP(j,w) if (b[i][j] == 9) p[i][j] = 1;
  REP(i,h) REP(j,w) {
    if (p[i][j]) continue;
    int ok = 1;
    REP(k,4) {
      int ny = i + dy[k], nx = j + dx[k];
      if (ny < 0 || h <= ny) continue;
      if (nx < 0 || w <= nx) continue;
      if (p[ny][nx]) continue;
      if (b[ny][nx] <= b[i][j])  ok = 0;
    }
    if (ok) v.epb(dfs(i,j));
  }
  ll res = 1;
  sort(all(v));
  reverse(all(v));
  REP(i,3) res *= v[i];
   cout << res << endl; 
  return 0;
}

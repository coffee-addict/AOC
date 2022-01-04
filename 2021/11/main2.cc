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

const int N = 10;
int b[N][N], p[N][N];
int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

void dfs(int y, int x, int n) {
  if (b[y][x]) return;
  if (p[y][x]) return;
  p[y][x] = 1;
  REP(i,8) {
    int ny = y + dy[i], nx = x + dx[i];
    if (ny < 0 || n <= ny) continue;
    if (nx < 0 || n <= nx) continue;
    if (b[ny][nx]) b[ny][nx] = (b[ny][nx]+1)%10;
    dfs(ny,nx,n);
  }
}

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  int s; cin >> s;
  int n; cin >> n;
  REP(i,n) {
    string x; cin >> x;
    REP(j,n) b[i][j] = (int)(x[j]-'0');
  }
  REP(ss,s) {
    int ok = 1;
    memset(p, 0, sizeof(p));
    REP(i,n) REP(j,n) b[i][j] = (b[i][j]+1)%10;
    REP(i,n) REP(j,n) dfs(i,j,n);
    REP(i,n) REP(j,n) if (b[i][j]) ok = 0;
    if (ok == 0) continue;
    cout << ss+1 << endl;
  }
  return 0;
}


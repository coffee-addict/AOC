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

const int INF = 1000000000;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  int h, w; cin >> h >> w; 
  VVI b(h, VI(w));
  REP(i,h) {
    string s; cin >> s;
    REP(j,w) b[i][j] = (int)(s[j]-'0');
  }
  int d[5][5][h][w];
  REP(n,5) REP(m,5) REP(i,h) REP(j,w) d[n][m][i][j] = INF;
  queue<tuple<int,int,int>> q;
  q.push(mkt(0,0,0));
  REP(n,5) REP(m,5) {
    if (0 < n) REP(j,w) {
      int bb = (b[0][j] + n + m - 1)%9 + 1;
      d[n][m][0][j] = min(d[n][m][0][j], d[n-1][m][h-1][j] + bb);
      q.push(mkt(d[n][m][0][j],0,j));
    }
    if (0 < m) REP(i,h) {
      int bb = (b[i][0] + n + m - 1)%9 + 1;
      d[n][m][i][0] = min(d[n][m][i][0], d[n][m-1][i][w-1] + bb);
      q.push(mkt(d[n][m][i][0],i,0));
    }
    while (q.size()) {
      int r, y, x;
      tie(r,y,x) = q.front(); q.pop();
      REP(i,4) {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 0 || h <= ny) continue;
        if (nx < 0 || w <= nx) continue;
        int bb = (b[ny][nx] + n + m - 1)%9 + 1;
        if (d[n][m][ny][nx] <= r + bb) continue;
        d[n][m][ny][nx] = r + bb;
        q.push(mkt(d[n][m][ny][nx],ny,nx));
      }
    }
  }
  cout << d[4][4][h-1][w-1] << endl;
  return 0;
}

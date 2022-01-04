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

const int N = (26*26)*2 + 10;
int p[N];

int get_id(string s) {
  int res = 0;
  if (s == "start")
    res = (int)(N-2);
  else if (s == "end")
    res = (int)(N-1);
  else {
    int p = (int)(s[0]-'a');
    if (0 <= p && p < 26) {
      res = p*26 + (int)(s[1]-'a');
    } else {
      res = (int)(s[0]-'A')*26 + (int)(s[1]-'A') + (26*26);
    }
  }
  return res;
}

int dfs(int s, vector<vector<edge<int>>> &es) {
  if (s == (int)(N)-1) return 1;
  int res = 0;
  p[s] = 1;
  REP(i,es[s].size()) {
    int t = es[s][i].to;
    if (p[t] == 0 || (26*26 <= t && t < 1352) || t == (int)N-1)
      res += dfs(t,es);
  }
  p[s] = 0;
  return res;
}

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  int cases; cin >> cases; 
  REP(cc,cases) {
    vector<vector<edge<int>>> es(N);
    int n; cin >> n; 
    REP(i,n) {
      string s; cin >> s; 
      int x = (int)(s.find("-"));
      string s0 = s.substr(0,x), s1 = s.substr(x+1);
      int f = get_id(s0), t = get_id(s1);
      es[f].epb(edge<int>(f,t,0));
      es[t].epb(edge<int>(t,f,0));
//cout << "f -> t = "  << f << " -> " << t << endl;
    }
    memset(p, 0, sizeof(p));
    cout << dfs((int)N-2, es) << endl;
  }
  return 0;
}

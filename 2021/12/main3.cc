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

const int M = 26;
const int N = M*M*2 + 10;
int p[N];

int encode(string s) {
  int res = 0;
  if (s == "start")
    res = (int)(N-2);
  else if (s == "end")
    res = (int)(N-1);
  else {
    int p = (int)(s[0]-'a');
    if (0 <= p && p < M) {
      res = p*M + (int)(s[1]-'a');
    } else {
      res = (int)(s[0]-'A')*M + (int)(s[1]-'A') + (M*M);
    }
  }
  return res;
}

string decode(int x) {
  string res = "";
  if (x == (int)N-2)
    res = "start";
  if (x == (int)N-1)
    res = "end";
  else {
    if (x < M*M) {
      res += (char)('a' + (x/M)%M);
      res += (char)('a' + x%M);
    } else {
      x -= M*M;
      res += (char)('A' + (x/M)%M);
      res += (char)('A' + x%M);
    }
  }
  return res;
}

void dfs(int s, string x, VVE &es, set<string> &res) {
  if (s == (int)(N)-1) {
    res.insert(x + "end");
    return;
  }
  x += decode(s);
  p[s]++;
  REP(i,es[s].size()) {
    int t = es[s][i].to;
    if (0 <= t && t < M*M && p[t] == 1) continue;
    if (t == (int)N-2) continue;
    dfs(t,x,es,res);
  }
  p[s]--;
}

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  int cases; cin >> cases; 
  REP(cc,cases) {
    VVE es(N);
    int n; cin >> n; 
    REP(i,n) {
      string s; cin >> s; 
      int x = (int)(s.find("-"));
      string sl = s.substr(0,x), sr = s.substr(x+1);
      int l = encode(sl), r = encode(sr);
      es[l].epb(edge<int>(l,r,0));
      es[r].epb(edge<int>(r,l,0));
    }
    set<string> res;
    REP(i,M*M) {
      memset(p, 0, sizeof(p));
      p[i] = -1;
      if (es[i].empty()) continue;
      dfs((int)N-2,"",es,res);
    }
    cout << res.size() << endl; 
  }
  return 0;
}

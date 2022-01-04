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

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  int n; cin >> n; 
  VI p = {0, 3, 57, 1197, 25137};
  int res = 0;
  REP(i,n) {
    string s; cin >> s; 
    int m = (int)s.size();
    VI d, sgn;
    REP(j,m) {
      if (s[j] == '(') {
        d.epb(1);
        sgn.epb(1);
      } else if (s[j] == ')') {
        d.epb(1);
        sgn.epb(-1);
      } else if (s[j] == '[') {
        d.epb(2);
        sgn.epb(1);
      } else if (s[j] == ']') {
        d.epb(2);
        sgn.epb(-1);
      } else if (s[j] == '{') {
        d.epb(3);
        sgn.epb(1);
      } else if (s[j] == '}') {
        d.epb(3);
        sgn.epb(-1);
      } else if (s[j] == '<') {
        d.epb(4);
        sgn.epb(1);
      } else if (s[j] == '>') {
        d.epb(4);
        sgn.epb(-1);
      }
    }
    stack<int> st;
    REP(j,m) {
      int x = d[j];
      if (sgn[j] > 0)
        st.push(x);
      else {
        int y = st.top();
        if (x != y) {
          res += p[x];
          break;
        }
        st.pop();
      }
    }
  }
  cout << res << endl; 
  return 0;
}

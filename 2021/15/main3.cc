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

template<class T>
struct edge {
  int from;
  int to;
  T cost;

  edge(int f, int t, T c) {
    from = f;
    to   = t;
    cost = c;
  }
};

template<class T>
struct graph_shortest_path {
  T inf;
  int nv;
  vector<T> dist;
  vector<T> visited;
  vector<T> rev_path;
  vector<T> min_path;
  vector<vector<edge<T>>> es;

  graph_shortest_path(int _nv, T _inf) {
    inf = _inf; 
    nv = _nv;
    dist.resize(nv);
    visited.resize(nv);
    rev_path.resize(nv);
    es.resize(nv);
  }

  void set_edge(int from, int to, T cost) {
    es[from].push_back(edge<T>(from, to, cost));
  }

  //BellmanFord O(nv*ne)
  void calc_bellman_ford(int s) {
    fill(all(dist), inf);
    dist[s] = 0;
    REP(u,nv-1) {
      REP(i,nv) REP(j,(int)es[i].size()) {
        edge<T> e = es[i][j];
        if (dist[e.from] == inf) continue;
        if (dist[e.to] > dist[e.from] + e.cost)
          dist[e.to] = dist[e.from] + e.cost;
      }
    }
  }

  //O(nv*ne)
  int check_negative_loop() {
    fill(all(dist), 0);
    REP(u,nv) {
      REP(i,nv) REP(j,(int)es[i].size()) {
        edge<T> e = es[i][j];
        if (dist[e.to] > dist[e.from] + e.cost) {
          dist[e.to] = dist[e.from] + e.cost;
          if (u == nv-1) return 1;
        }
      }
    }
    return 0;
  }

  void dijkstra(int s) {
    priority_queue<tuple<T,int>, vector<tuple<T,int>>, greater<tuple<T,int>>> q;
    fill(all(dist),inf);
    dist[s] = 0;
    q.push(make_tuple(0,s));
    while (q.size()) {
      int v;
      T d;
      tie(d, v) = q.top();
      q.pop();
      if (dist[v] < d) continue;
      REP(i,es[v].size()) {
        edge<T> e = es[v][i];
        T x = dist[v] + e.cost;
        if (dist[e.to] <= x) continue;
        dist[e.to] = x;
        rev_path[e.to] = v;
        q.push(make_tuple(dist[e.to],e.to));
      }
    }
  }

  //set minimum dist/cost path(start -> goal)
  void set_shortest_path(int start, int goal) {
    min_path.clear();
    min_path.push_back(goal);
    int pos = goal;
    while (1) {
      min_path.push_back(rev_path[pos]);
      if (rev_path[pos] == start)
        break;
      pos = rev_path[pos];  
    }
    reverse(all(min_path));
  }
};

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
  graph_shortest_path<int> g(h*5*w*5, INF);
  REP(n,5) REP(m,5) REP(i,h) REP(j,w) {
    int y = n*h + i, x = m*w + j;
      REP(k,4) {
        int ny = y + dy[k], nx = x + dx[k];
        if (ny < 0 || h*5 <= ny) continue;
        if (nx < 0 || w*5 <= nx) continue;
        int bb = (b[ny%h][nx%w] + (ny/h) + (nx/w) - 1)%9 + 1;
        int f = y*w*5 + x, t = ny*w*5 + nx;
        g.set_edge(f, t, bb);
      }
  }
  g.dijkstra(0);
  cout << g.dist[g.dist.size()-1] << endl;
  return 0;
}

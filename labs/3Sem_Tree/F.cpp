#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long long;
 
int const N = (int)2e5 + 7;
int const M = 1000*1000*1000 + 7;
 
int n, m;
int c[N] = {};
int fa[N];
int sz[N];
int root_dist[N];
int dist_cent[N];
bool done[N];
vector<int> g[N];
 
int tin[N];
int st[20][N+N];
vector<int> euler;
 
void tour(int u, int p = 0) {
  root_dist[u] = root_dist[p] + 1;
 
  tin[u] = euler.size();
  euler.emplace_back(u);
 
  for(int v : g[u]) {
    if(v == p)
      continue;
 
    tour(v, u);
    euler.emplace_back(u);
  }
}
 
void build() {
  int n = euler.size();
 
  for(int i = 0; i < n; ++i) {
    st[0][i] = euler[i];
  }
 
  for(int j = 1; (1<<j) <= n; ++j) {
    int b = 1 << (j-1);
    int lim = b+b-1;
 
    for(int i = 0; i + lim < n; ++i) {
      int x = st[j-1][i];
      int y = st[j-1][i+b];
      st[j][i] =  (root_dist[x] < root_dist[y] ? x : y);
    }
  }
}
 
int lca(int u, int v) {
  int l = tin[u];
  int r = tin[v];
 
  if(l > r) swap(l, r);
 
  int b = 31 - __builtin_clz(r-l+1);
  int x = st[b][l];
  int y = st[b][r-(1<<b)+1];
  return (root_dist[x] < root_dist[y] ? x : y);
}
 
int calc_dist(int u, int v) {
  return root_dist[u] + root_dist[v] - 2*root_dist[lca(u, v)];
}
 
void dfs(int u, int p) {
  sz[u] = 1;
  for(int v : g[u]) {
    if(done[v] || v == p)
      continue;
    dfs(v, u);
    sz[u] += sz[v];
  }
}
 
int dfs_cent(int u, int p, int tot) {
  for(int v : g[u]) {
    if(done[v] || v == p)
      continue;
 
    if(sz[v] + sz[v] > tot)
      return dfs_cent(v, u, tot);
  }
  return u;
}
 
ll total[N];
ll col[2][N];
ll dist[2][20][N];
ll cnt_col[2][N];
ll cnt_dist[2][20][N];
 
int centroid(int u, int level) {
  dfs(u, 0);
 
  int center = dfs_cent(u, 0, sz[u]);
 
  u = center;
 
  dist_cent[center] = level;
 
  done[center] = true;
 
  for(int v : g[center])
    if(not done[v])
      fa[centroid(v, level+1)] = center;
 
  return center;
}
 
void toggle(int u) {
  int old = c[u];
  c[u] ^= 1;
 
  int p = 0;
  for(auto center = u; center; center = fa[center]) {
    int d = calc_dist(u, center);
    int idx = dist_cent[center];
 
    col[old][center] -= d;
    col[old^1][center] += d;
 
    cnt_col[old][center]--;
    cnt_col[old^1][center]++;
 
 
 
    if(p) {
      dist[old][idx][p] -= d;
      dist[old^1][idx][p] += d;
 
      cnt_dist[old][idx][p] --;
      cnt_dist[old^1][idx][p] ++;
    }
 
    p = center;
  }
}
 
void add(int u) {
  int old = c[u];
 
  int p = 0;
  for(auto center = u; center; center = fa[center]) {
    int d = calc_dist(u, center);
    int idx = dist_cent[center];
 
    col[old][center] += d;
    cnt_col[old][center] ++;
 
    if(p) {
      dist[old][idx][p] += d;
      cnt_dist[old][idx][p] ++;
    }
 
    p = center;
  }
}
 
ll query(int u) {
  int old = c[u];
 
  int p = 0;
 
  ll ans = 0;
 
  for(auto center = u; center; center = fa[center]) {
    int d = calc_dist(u, center);
 
    int idx = dist_cent[center];
 
    ans += col[old][center] + cnt_col[old][center] * calc_dist(u, center);
 
    if(p) ans -= dist[old][idx][p] + cnt_dist[old][idx][p] * calc_dist(u, center);
 
    p = center;
  }
 
  return ans;
}
 
int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);
 
  cin >> n >> m;
 
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
 
  tour(1, 0);
  build();
  centroid(1, 0);
 
  for(int i = 1; i <= n; ++i)
    add(i);
 
  while(m--) {
    int t, v;
    cin >> t >> v;
 
    if(t & 1) {
      toggle(v);
    } else {
      cout << query(v) << "\n";
    }
  }
}
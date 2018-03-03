#include <bits/stdc++.h>
 
using namespace std;
int n;
vector<vector< int> > v;
vector<int> parent;
vector<int> depth;
vector<int> treePos;
vector<int> root;
vector<int> heavy;
vector<int> t;
 
 
int dfs(int u,int p = -1){
    int si = 1;
    int curMaxSub = 0;
    parent[u] = p;
    for(auto &to: v[u])
        if(to != p) {
            depth[to] = depth[u] + 1;
            int curSub = dfs(to, u);
            if(curSub > curMaxSub)curMaxSub = curSub, heavy[u] = to;
 
            si += curSub;
        }
 
    return si;
}
 
 
 
void build() {
  for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}
 
void init_HLD(int n){
    heavy.resize(n, -1);
    parent.resize(n);
    depth.resize(n);
    treePos.resize(n);
    root.resize(n);
    depth[0] = 0;
    dfs(0);
    for(int i = 0, cur  = 0; i < n; i++){
        if(parent[i] == -1 || heavy[parent[i]] != i)
        for(int j = i;j != -1; j = heavy[j]){
            root[j] = i;
            treePos[j] = cur++;
        }
    }
    t.resize(2 * n, 0);
}
 
int query(int l) {
  int res = 0;
  for (l += n; l != 1; l >>= 1) {
    res += t[l];
  }
  return res;
}
 
 
void modify(int l, int r, int value = 1) {
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) t[l++] += value;
    if (r&1) t[--r] += value;
  }
}
 
void processPath(int u, int v) {
    for (; root[u] != root[v]; v = parent[root[v]]) {
      if (depth[root[u]] > depth[root[v]]) swap(u, v);
      modify(treePos[root[v]], treePos[v] + 1 );
    }
    if (depth[u] > depth[v]) swap(u, v);
        modify(treePos[u], treePos[v] + 1);
    u = depth[u] > depth[v] ? v : u;
    modify(treePos[u], treePos[u] + 1, -1);
 
  }
 
 
int main()
{
   int  m;
 
    cin >> n >> m;
    v.resize(n);
    for(int i = 0 ;i<n -1;i++){
        int a, b;
        cin >> a>>b;
        v[a-1].push_back(b-1);
        v[b-1].push_back(a-1);
    }
    init_HLD(n);
 
    for(int i = 0 ;i<m;i++){
 
        char c;
        int a,  b;
        cin >> c>> a>> b;
        a--;
        b--;
        if(c=='P'){
            processPath(a, b);
 
 
        }
        else {
                b = b == parent[a] ? a : b;
            cout << query(treePos[b]) <<endl;
            //a = query(treePos[b]);
//            int y ;
//            con >> y;
//            if(y != a){
//                cout << "NO";
//                return 0;
//            }
 
        }
    }
    //cout << "YES";
 
}
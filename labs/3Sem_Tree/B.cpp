#include <bits/stdc++.h>
 
using namespace std;
int n;
vector<vector< int> > v;
vector<int> parent;
vector<int> depth;
vector<int> treePos;
vector<int> root;
vector<int> h;
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
 
 
 
void modify(int p, int value) {
    p += n;
  for (t[p] = value; p > 1; p >>= 1) t[p>>1] = max(t[p],t[p^1]);
}
void build() {
    for(int i = 0;i < n;i++){
        modify(treePos[i], h[i]);
    }
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
    build();
}
 
int query(int l, int r) {
  int res = -113312;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = max(res,t[l++]);
    if (r&1) res = max(res,t[--r]);
  }
  return res;
}
 
int processPath(int u, int v) {
    int res = -113211;
    for (; root[u] != root[v]; v = parent[root[v]]) {
      if (depth[root[u]] > depth[root[v]]) swap(u, v);
      res = max(res,query(treePos[root[v]], treePos[v] + 1 ));
    }
    if (depth[u] > depth[v]) swap(u, v);
        res =  max(res,query(treePos[u], treePos[v] + 1));
    //u = depth[u] > depth[v] ? v : u;
   // modify(treePos[u], treePos[u] + 1, -1);
return res;
  }
 
 
int main()
{
   int  m;
    ifstream cin("mail.in");
    ofstream cout("mail.out");
    cin >> n ;
    v.resize(n);
    h.resize( n);
    for(int i = 0 ;i<n ;i++){
        cin >> h[ i];
    }
    for(int i = 0 ;i<n -1;i++){
        int a, b;
        cin >> a>>b;
        v[a-1].push_back(b-1);
        v[b-1].push_back(a-1);
    }
    init_HLD(n);
    cin >> m;
    for(int i = 0 ;i<m;i++){
 
        char c;
        int a,  b;
        cin >> c>> a>> b;
        a--;
        b--;
        if(c=='?'){
               // cout <<" S";
            cout << processPath(a, b) << endl;
 
//            modify(treePos[a], b+1);
//            for(int i = 0 ;i < 2 *n;i++){
//                cout << t[i] << " ";
//            }
//            cout <<endl;
 
 
        }
        else {
            modify(treePos[a], b+1);
//            for(int i = 0 ;i < 2 *n;i++){
//                cout << t[i] << " ";
//            }
//            cout <<endl;
 
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
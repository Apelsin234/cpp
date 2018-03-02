#include <bits/stdc++.h>
 
using namespace std;
 
vector<vector<int> > v;
 
vector<int> parent;
vector<int> depth;
vector<int> used;
vector<vector<int>> up;
int t = 0;
int l ;
void dfs(int u ,int p, int d  = 0){
    up[u][0] = p;
 
    depth[u] = d;
    for(int i = 1;i <= l;i++){
        up[u][i] = up[up[u][i-1]][i-1];
    }
    for(int i = 0; i  < v[u].size();i++){
            int to = v[u][i];
        if( to != p){
            dfs(to , u, d + 1);
        }
    }
 
}
 
void foo(int u, int p){
    up[u][0] = p;
    parent[u] = p;
    for(int i = 1;i <= l;i++){
        up[u][i] = up[up[u][i-1]][i-1];
    }
    depth[u] = depth[p] + 1;
}
 
 
 
int lca (int a, int b) {
    if(depth[a] > depth[b])
        swap(a,b);
    for (int i=l; i>=0; --i)
    {
        if(depth[b] - depth[a] >= pow(2,i)){
            b = up[b][i];
        }
 
    }
    if(a==b)return a;
    for (int i=l; i>=0; --i)
    {
        if(up[a][i]!=up[b][i]){
                a = up[a][i];
                b = up[b][i];
        }
 
    }
    return up[a][0];
}
vector<int> dsu;
 void dsuInit(int n){
    dsu.resize(n);
    for(int i = 0 ;i<n;i++){
        dsu[i] = i;
    }
 }
 
 int dsuFind(int a){
    return dsu[a] = a == dsu[a] ? a : dsuFind(dsu[a]);
 }
 
 bool dsuUnion(int a, int b){
     a = dsuFind(a);
     b = dsuFind(b);
     if(a != b){
    dsu[b] = a;
     return true;
     }
     return false;
 
 }
 
int main()
{
 
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
 
ifstream cin("lca3.in");
   ofstream cout("lca3.out");
    int n;
    cin>>n;
    n++;
    v.resize(n);
    parent.resize(n);
    depth.resize(n, 0);
    used.resize(n, true);
    up.resize (n);
    l = 1;
    while ((1<<l) <= n)  ++l;
    for (int i=0; i<n; ++i)  up[i].resize (l+1);
    int k = 1;
    dsuInit(n);
    for(int i =1;i<n;i++){
        int a;
        cin >> a;
        if(a != 0){
            v[a].push_back(i);
            used[i] = false;
            dsuUnion(a,i);
        }
    }
    for(int i = 1;i<n;i++){
        if(used[i] ){
            dfs(i, i);
        }
    }
 
    int m ;
    cin>>m;
    int t = 0;
    n--;
    for(int i = 0;i<m;i++){
           int x,y,c;
           cin>>c>>x>>y;
           int u = ((x - 1 + t)%n) + 1;
           int q = ((y - 1 + t)%n) + 1;
           if(c == 0){
            if(dsuFind(u) != dsuFind(q)){
                t = 0;
            } else {
                t = lca(u, q);
            }
            cout << t <<endl;
           } else {
               u = dsuFind(u);
                dsuUnion(q, u);
                v[q].push_back(u);
                dfs(u, q, depth[q] + 1);
 
 
           }
    }
 
 
    return 0;
}
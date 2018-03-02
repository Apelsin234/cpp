#include <bits/stdc++.h>
 
using namespace std;
 
 
 
 
vector<vector<pair<int,int>> > v;
 
vector<bool> b;
vector<int> tin;
vector<int> tout;
int N = (int)1e6;
vector<vector<int>> up;
vector<vector<int>> min_up;
int t = 0;
int l;
void dfs(int u ,int p = 0,int w = N){
    tin[u] = ++t;
    up[u][0] = p;
    min_up[u][0] =  w;
    b[u] = true;
    for(int i = 1;i <= l;i++){
        up[u][i] = up[up[u][i-1]][i-1];
        min_up[u][i]  =min(min_up[up[u][i-1]][i-1],min_up[u][i-1] );
    }
    for(int i = 0; i  < v[u].size();i++){
            int to = v[u][i].first;
        if(!b[to] && to != p){
            dfs(to , u, v[u][i].second);
        }
    }
    tout[u] = ++t;
 
}
bool upper (int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}
 
int lca (int a, int b) {
    if (upper (a, b))  return N;
    //if (upper (b, a))  return N;
    int o = min_up[a][0];
    for (int i=l; i>=0; --i)
        if (! upper (up[a][i], b)){
 
            o = min(o, min_up[a][i]);
            a = up[a][i];
            //o = min(o, min_up[a][i]);
            }
    return min(min_up[a][0], o);
}
 
 
int main()
{
    ifstream cin("minonpath.in");
   ofstream cout("minonpath.out");
    int n;
    cin >> n;
    b.resize(n, 0);
    v.resize(n);
    for(int i = 1;i<n;i++){
        int a,b;
        cin>>a>>b;
        v[a - 1].push_back({i, b});
    }
    tin.resize (n),  tout.resize (n),  up.resize (n), min_up.resize(n);
    l = 1;
    while ((1<<l) <= n)  ++l;
    for (int i=0; i<n; ++i){  up[i].resize (l+1);
     min_up[i].resize (l+1);}
    dfs(0);
 
    int m;
    cin >> m;
    for(int i = 0 ;i<m;i++){
        int a,b;
        cin >> a>> b;
        a--;
        b--;
    cout << min(lca(a, b), lca(b, a))<<endl;
 
    }
 
    return 0;
}
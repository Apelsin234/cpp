#include <bits/stdc++.h>
 
using namespace std;
 
 
 
 
vector<vector<pair<int,int>> > v;
 
vector<int> tin;
vector<int> tout;
int N = (int)1e6;
vector<vector<int>> up;
vector<vector<int>> min_up;
int t = 0;
int l;
void dfs(int u ,int p = 0,int w = 0){
    tin[u] = ++t;
    up[u][0] = p;
    min_up[u][0] =  w;
    for(int i = 1;i <= l;i++){
        up[u][i] = up[up[u][i-1]][i-1];
        min_up[u][i] = min_up[up[u][i-1]][i-1] + min_up[u][i-1] ;
    }
    for(int i = 0; i  < v[u].size();i++){
            int to = v[u][i].first;
        if( to != p){
            dfs(to , u, v[u][i].second);
        }
    }
    tout[u] = ++t;
 
}
bool upper (int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}
 
int lca (int a, int b) {
    if (upper (a, b))  return  0;
    //if (upper (b, a))  return N;
    //int o = min_up[a][0];
    int o = 0;
    for (int i=l; i>=0; --i)
        if (! upper (up[a][i], b)){
 
            o +=  min_up[a][i] ;
            a = up[a][i];
            //o = min(o, min_up[a][i]);
            }
    return o + min_up[a][0];
}
 
 
int main()
{
    ifstream cin("tree.in");
   ofstream cout("tree.out");
    int n;
    cin >> n;
    v.resize(n);
    for(int i = 1;i<n;i++){
        int a,b,c;
        cin>>a>>b>>c;
        v[a].push_back({b, c});
        v[b].push_back({a, c});
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
    if(a == b){
        cout << 0 << endl;
    }else
    cout <<(lca(a, b) + lca(b, a))<<endl;
 
    }
 
    return 0;
}
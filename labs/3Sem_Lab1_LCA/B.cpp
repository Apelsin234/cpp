#include <bits/stdc++.h>
 
using namespace std;
 
vector<vector<int> > v;
vector<pair<int, int> > q;
 
vector<int> tin;
vector<int> tout;
vector<vector<int>> up;
int t = 0;
int l ;
void dfs(int u ,int p = 0 ){
    tin[u] = ++t;
    up    [u][0] = p;
    for(int i = 1;i <= l;i++){
        up[u][i] = up[up[u][i-1]][i-1];
    }
    for(int i = 0; i  < v[u].size();i++){
            int to = v[u][i];
        if( to != p){
            dfs(to , u);
        }
    }
    tout[u] = ++t;
 
}
bool upper (int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}
 
int lca (int a, int b) {
    if (upper (a, b))  return a;
    if (upper (b, a))  return b;
    for (int i=l; i>=0; --i)
        if (! upper (up[a][i], b))
            a = up[a][i];
    return up[a][0];
}
 
 
int main()
{
    ifstream cin("lca.in");
    ofstream cout("lca.out");
    int n ;
    int k;
    cin >> k;
    for(int i = 0;i<k;i++){
        int a, b;
        string s;
        cin>>s >> a>> b;
        n = max(a,max(b,n));
        v.resize(n);
        a--;
        b--;
        if(s == "GET"){
            q.push_back({a,b});
        } else {
            v[a].push_back(b);
        }
    }
    tin.resize (n),  tout.resize (n),  up.resize (n);
    while ((1<<l) <= n)  ++l;
    for (int i=0; i<n; ++i)  up[i].resize (l+1);
    dfs(0);
 
 
    for(int i = 0 ;i<q.size();i++){
        int a, b;
        tie(a, b) = q[i];
        cout << lca(a,b) + 1 << endl;
    }
 
    return 0;
}
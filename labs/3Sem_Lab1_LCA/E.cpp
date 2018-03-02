#include <bits/stdc++.h>
 
using namespace std;
 
vector<vector<int> > v;
 
vector<int> tin;
vector<int> depth;
vector<int> tout;
vector<vector<int>> up;
int t = 0;
const int N = (int)1e6;
int l ;
void dfs(int u,int p = 0,int d = 0) {
    tin[u] = ++t;
    up[u][0] = p;
    depth[u] = d;
    for(int i = 1; i <= l; i++) {
        up[u][i] = up[up[u][i-1]][i-1];
    }
    for(int i = 0; i  < v[u].size(); i++) {
        int to = v[u][i];
        if( to != p) {
            dfs(to, u, d + 1);
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
 
 
int main() {
 ifstream cin("dynamic.in");
     ofstream cout("dynamic.out");
 
 
    int n;
        while(cin >> n && n != 0) {
    v.assign(n,vector<int>());
    tin.resize(n),  tout.resize (n),  up.resize (n);
    depth.resize(n);
    l = 1;
    while ((1<<l) <= n)  ++l;
    for (int i=0; i<n; ++i)  up[i].resize (l+1);
        for(int i = 1; i<n; i++) {
            int a, b;
            cin>>a >> b;
            b--;
            a--;
            v[a].push_back(b);
            v[b].push_back(a);
        }
        l = 1;
        while ((1<<l) <= n)  ++l;
        int root = -1;
        int rootNew = 0;
        dfs(0);
 
        int m;
        cin >> m;
        for(int i = 0 ; i<m; i++) {
            int a,b;
            char c;
            cin >> c ;
            if(c == '?') {
                cin >> a>> b;
                int otv ;
                int q = lca(a -1,b -1);
                int w = lca(a - 1, rootNew);
                int e = lca(b - 1, rootNew);
                if(depth[q] < depth[w]) {
                    otv = w;
                } else {
                    otv = q;
                }
                if(depth[otv] < depth[e]) {
                    otv= e;
                }
                cout <<otv + 1<< endl;
            } else {
                cin >> rootNew;
                rootNew--;
            }
        }
    }
    return 0;
}
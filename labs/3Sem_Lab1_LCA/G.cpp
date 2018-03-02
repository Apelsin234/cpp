#include <bits/stdc++.h>
 
using namespace std;
 
vector<vector<int> > v;
 
vector<int> tin;
vector<int> parent;
vector<int> depth;
vector<int> used;
vector<int> tout;
vector<vector<int>> up;
int t = 0;
int l ;
void dfs(int u ,int p = 0){
    tin[u] = ++t;
    up[u][0] = p;
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
 
int alive(int a){
    if(!used[a] ){
        return parent[a] = alive(parent[a]);
    }
    return a;
}
 
int main()
{
    ifstream cin("carno.in");
    ofstream cout("carno.out");
    int n;
    cin>>n;
    v.resize(n);
    parent.resize(n);
    depth.resize(n);
    used.resize(n, true);
    up.resize (n);
    l = 1;
    while ((1<<l) <= n)  ++l;
    for (int i=0; i<n; ++i)  up[i].resize (l+1);
    int k = 1;
    foo(0, 0);
    depth[0] = 0;
 
    for(int i = 0;i<n;i++){
            char ch;
            cin >>ch;
            if(ch == '-'){
                int a;
                cin>>a;
                used[a-1] = false;
            }
            if(ch == '+'){
                    int a;
                cin >> a;
                foo(k, a - 1);
                k++;
 
            }
            if(ch == '?'){
                    int a,b;
                cin>>a>>b;
                a--;
                b--;
                cout<<alive(lca(a, b)) + 1<<endl;
 
            }
    }
 
 
    return 0;
}
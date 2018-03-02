#include <bits/stdc++.h>
 
using namespace std;
 
vector<vector<int> > v;
 
vector<int> parent;
vector<vector<int>> table;
vector<int> logn;
vector<int> p2;
vector<int> depth;
vector<int> ePath;
vector<vector<int>> up;
vector<int> FAI;
int ptr = 0;
int t = 0;
int l ;
void dfs(int u ,int p , int d  = 0){
    if (FAI[u]==-1)
        FAI[u] = ptr;
 
    depth[u] = d;
    ePath.push_back(u);
    ptr++;
    for(auto &to:v[u]){
        if( to != p){
            dfs(to , u, d + 1);
            ePath.push_back(u);
            ptr++;
        }
    }
 
}
 
int lca(int u, int v){
        int fv = FAI[v];
        int fu = FAI[u];
        if (fv > fu) {
            swap(fv, fu);
        }
        if (fu == fv) {
            return v;
        }
        int curLog = logn[(fu - fv + 1)];
        int deg = p2[curLog];
        int ans;
        if (depth[table[curLog][fv]] > depth[table[curLog][fu - deg + 1]]) {
            ans = table[curLog][fu - deg + 1];
        } else {
            ans = table[curLog][fv];
        }
        return ans;
 
}
 
void preprocess(int n)
{
    p2.resize(20);
    p2[0] = 1;
    for (long long i=1; i<20; i++)
        p2[i] = p2[i-1]*2;
    logn.resize(n + 1);
    long long val = 1,ptr=0;
    for (long long i=1; i<=n; i++)
    {
        logn[i] = ptr-1;
        if (val==i)
        {
            val*=2;
            logn[i] = ptr;
            ptr++;
        }
    }
}
 
 
void sparseTable() {
    int log = logn[ePath.size()] + 1;
    int n = ePath.size();
 
    table.resize(log, vector<int>(n));
 
    for(auto i = 0;i<n;i++){
        table[0][i] = ePath[i];
    }
    for(int i = 1 ;i<log;i++){
        for(int j = 0; j < n - p2[i] + 1; j++){
            if (depth[table[i - 1][j]] > depth[table[i - 1][j + p2[i-1]]]) {
                    table[i][j] = table[i - 1][j + p2[i-1]];
                } else {
                    table[i][j] = table[i - 1][j];
                }
        }
    }
 
 
}
 
void addEdge(int a,int b){
    v[a].push_back(b);
    v[b].push_back(a);
}
 
 
int main()
{
 
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    ifstream cin("lca_rmq.in");
    ofstream cout("lca_rmq.out");
    long long m,n;
    cin >> n >> m;
 
 
    FAI.resize(n, -1);
    depth.resize(n);
    v.resize(n);
 
    for(long long i = 1;i<n ;i++){
        long long a;
        cin>>a;
        addEdge(a, i );
    }
    ptr = 0;
    dfs(0,0);
 
    preprocess(ePath.size());
    sparseTable();
 
 
    long long a,b;
    cin >> a >> b;
    long long x ,y , z;
    long long v = 0;
    cin >> x >> y>>z;
    long long ans = 0;
    for(long long i = 0;i<m;i++){
         v = lca(((a + v) % n) , b ) ;
         ans +=v;
        a =( x * (a ) + y * (b ) + z)%n;
        b = (x * (b ) + y * (a ) + z)%n;
 
    }
    cout << ans << endl;
 
   // ifstream cin("lca3.in");
   //ofstream cout("lca3.out");
 
    return 0;
}
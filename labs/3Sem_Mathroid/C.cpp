#include <bits/stdc++.h>
 
using namespace std;
#define all(collection) begin(collection),end(collection)
#define srt(collection) sort(all(collection))
#define fori(index_name, from_i, to_i) for(int index_name = from_i; index_name< to_i; ++index_name)
#define each(element, collection) for(auto &element: collection)
#define each2(iterator_name, collection) for(auto iterator_name = begin(collection); iterator_name != end(collection); ++iterator_name)
#define rep(index_name, col_size) fori(index_name, 0, col_size)
 
typedef vector<int> VI;
typedef vector<bool> VB;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef vector<PII> VPII;
typedef long long LL;
VVI g;
VB used;
VI ans;
 
bool dfs(int u){
    if(used[u]) {
        return false;
    }
    used[u] = true;
 
    each(to,g[u]){
        if(ans[to] == -1 || dfs(ans[to])){
        ans[to] = u;
        return true;
        }
    }
    return false;
}
 
 
int main() {
    ios_base::sync_with_stdio(false);
    ifstream cin("matching.in");
    ofstream cout("matching.out");
    int n;
    cin >> n;
    VPII s(n);
    rep(i, n){
        int k;
        cin >> k;
        s[i] = {k, i};
    }
    sort(all(s),[](PII a, PII b){
        return a.first > b.first;
    });
//    for(int i = 0; i < n; i++){
//        cout << s[i].second << " ";
//    }
    cout << endl;
    g.resize(n);
    rep(i, n){
        int q;
        cin >> q;
        g[i].resize(q);
        rep(j, q){
            int w;
            cin >> w;
            g[i][j] = w - 1;
        }
    }
    ans.resize(n, -1);
    rep(i, n){
        used.assign(n, false);
        dfs(s[i].second);
    }
//    for(int i = 0; i < n; i++){
//        cout << ans[i] + 1 << " " << i + 1 << endl;
//    }
    VI res(n, -1);
    rep(i, n){
        if(ans[i] != -1)
        res[ans[i]] = i;
    }
    each(i, res){
        cout << i + 1 << " ";
    }
    return 0;
}
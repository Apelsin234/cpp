#include <bits/stdc++.h>
 
using namespace std;
 
long long foo(long long n, long long m){
    long long otv = 1;
    m = max(m, n-m);
    for(long long i = m + 1; i <= n;i++){
        otv *= i;
    }
    for(long long i = 1; i <= n - m;i++){
        otv /= i;
    }
    return otv;
 
}
int bar(const set<int> & a){
    int y = 0;
    for(auto &i: a){
        y += (1 << i);
    }
    return y;
}
int main() {
    ios_base::sync_with_stdio(false);
    ifstream cin("cycles.in");
    ofstream cout("cycles.out");
    int n,m;
    cin >> n >> m;
    vector<int>weight(n);
    for(auto &i: weight){
        cin >> i;
    }
    vector<set<int> > v(m);
    set<int> s;
    for(int i=0;i<m;i++){
        int k;
        cin >> k;
        for(int j=0;j<k;j++){
            int a;
            cin >> a;
            v[i].emplace(a - 1);
        }
        s.emplace(bar(v[i]));
    }
    vector<bool> ans(pow(2, n),true);
    for(long long i = 0;i<pow(2,n);i++) {
        for(auto &j: s){
            if((j & i) == j){
                ans[i] = false;
                break;
            }
        }
    }
    int otv = 0;
//    for(int i = 0;i<ans.size();i++){
//        cout << (ans[i] ? 1 : 0) << " ";
//    }
//    cout << "\n";
    for(long long i = 0;i<pow(2,n);i++) {
 
        if(ans[i]){
         int ot = 0;
        for(int p = 0;p < n;p++){
            if(i & (1 << p)){
                ot += weight[p];
            }
        }
        otv = max(ot,otv);
        }
    }
    cout << otv;
    return 0;
}
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
 
long long bar(const set<long long> & a){
    long long y = 0;
    for(auto &i: a){
        y += (1 << i);
    }
    return y;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    ifstream cin("check.in");
    ofstream cout("check.out");
    long long n,m ;
    cin >> n >> m;
    vector<set<long long> >  v(m);
    set<long long > s;
    bool b1 = false;
    for(long long i = 0; i < m; i++){
        long long k;
        cin >> k;
        if(k == 0) b1 = true;
        for(long long j = 0; j < k ; j++){
            long long a;
            cin >> a;
            v[i].emplace(a - 1);
        }
        s.emplace( bar ( v[ i] ) ) ;
    }
    if(!b1){
        cout << "NO";
        return 0;
    }
    //s.emplace(1);
 
    ///////22222222222222222222222222//////////////
    for(long long i = 0;i < m;i++){
        long long y = 1;
        long long res = bar(v[i]);
        for(long long j =0;j < v[i].size() ;j++){
             //   cout << v[i].size() << " "<<j << endl;
            y += foo(v[i].size(), j + 1);
        }
        //cout << i << " "<< y << endl;
        for(auto &u: s){
            if((res & u) == u){
                y--;
            }
        }
        //cout << y <<endl;
        if(y != 0){
            cout << "NO";
            return 0;
        }
    }
//    for(long long i = 0;i<m;i++){
//            long long res = bar(v[i]);
//        for(auto &j:v[i]){
//            res -= (1 << j);
//            if(s.find(res) == s.end()){
//                cout << "NO";
//                return 0;
//            }
//            res += (1<<j);
//        }
//    }
    /////////////222222222222222222//////////////////
//    cout << "E" << endl;
//    for(auto &i : s){
//        cout <<i <<endl;
//    }
//    cout << ":PO\n";
    for(auto &i: v){
        for(auto &j : v){
           // if(__builtin_popcount(i) > __builtin_popcount(j)){
           if(i.size() > j.size()){
                long long u = bar(i);
                long long w = bar(j);
                bool ans = false;
//                for(auto &k : j){
//                    //if((u & (1 << k)) != 0)
//                    u &= ~(1 << k);
//                }
//                for(long long q = 0;q < 12;q++){
//                    if(long long o = (w | (u & (1 << q))) != w){
//                        if(s.find(o)==s.end()){
//
//                            cout << "NO";
//                            return 0;
//                        }
//                    }
//                }
                for(int q = 0;q < 12;q++){
                    if((u & (1 << q)) && (w & (1 << q))==0){
                        w += (1 << q);
                        if(s.find(w) != s.end()){
                            ans = true;
                        }
                        w -= (1 << q);
                    }
 
                }
                if(!ans){
                    cout <<"NO";
                    return 0;
                }
            }
        }
    }
            cout << "YES";
 
    return 0;
}
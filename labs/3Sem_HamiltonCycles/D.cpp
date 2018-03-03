#include <bits/stdc++.h>
 
using namespace std;
 
int main()
{
 
    ios_base::sync_with_stdio(0);
    ifstream cin("guyaury.in");
    ofstream cout("guyaury.out");
 
    cin.tie();
    cout.tie();
 
 
    int n;
    cin>>n;
 
    vector<vector<bool> > v(n, vector<bool>(n,false));
 
    for(int i = 0; i<n; i++) {
        for(int j = 0; j<i; j++) {
            char a;
            cin>>a;
            if(a=='1'){
                v[i][j] = !( v[j][i] = false);
            }else{
                v[i][j] = ! (v[j][i] = true);
            }
        }
    }
    vector<int> q(n);
    for(int i = 0;i<n;i++){
        q[i] = i;
    }
    while(true){
        random_shuffle(q.begin(),q.end());
    stable_sort(q.begin(),q.end(),[&v](int a, int b){
        return v[a][b];
    });
        if(v[q[n-1]][q[0]])break;
    }
    for(int &i: q){
        cout <<i + 1 << " ";
    }
    return 0;
}
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(0);
    ifstream cin("fullham.in");
    ofstream cout("fullham.out");
 
    cin.tie();
    cout.tie();
 
    int n;
    list<int> a;
    cin>>n;
    bool v[n][n];
    for(int i = 0;i<n;i++){
        v[i][i] = false;
    }
 
    for(int i = 0; i<n; i++) {
        for(int j = 0; j<i; j++) {
            char a;
            cin>>a;
            v[i][j] = v[j][i] = a== '1' ? true : false;
        }
    }
    int y = 0;
    for(int i = 0; i<n; i++) {
        a.push_back(i);
        if(i<n-1&&v[i][i+1]) {
            y++;
        }
    }
    if(v[0][n-1]) {
        y++;
    }
 
    for(int k  = 0; k<n*(n-1); k++) {
 
        auto i = a.begin();
        int q = *(i);
        ++i;
 
        auto w = i;
        ++i;
 
        if(!v[q][*w]) {
            while(!v[q][*(i++)] || !v[*w][*(i)]) {
 
            }
 
            reverse(w,i);
            y++;
            if(!v[*w][*i]) {
                y++;
            }
        }
 
        if(y==n) {
            break;
        }
        a.push_back(a.front());
        a.pop_front();
 
 
    }
 
    for(auto &i:a) {
        cout<<i + 1<<" ";
    }
    return 0;
}
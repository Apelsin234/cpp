#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(0);
    ifstream cin("chvatal.in");
    ofstream cout("chvatal.out");
 
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
    vector<int> aI(n);
    for(int i = 0; i<n; i++) {
            aI[i] = i;
    }
    random_shuffle(begin(aI),end(aI));
    for(int &i:aI) {
            a.push_back(i);
    }
    list<int> li;
 
    for(int k  = 0; k<n*(n-1); k++) {
        li.push_back(a.front());
        a.pop_front();
 
 
        if(!v[li.front()][a.front()]) {
        int v1 = li.back();
 
            li.push_back(a.front());
            a.pop_front();
            while(!v[v1][li.back()] ) {
                li.push_back(a.front());
            a.pop_front();
            }
            a.push_back(li.front());
            li.pop_front();
            while(!li.empty()){
            a.push_front(li.front());
            li.pop_front();}
        } else
 
 
        {
        a.push_back(li.back());
        li.pop_front();
        }
 
 
    }
 
    for(auto &i:a) {
        cout<<i + 1<<" ";
    }
    return 0;
}
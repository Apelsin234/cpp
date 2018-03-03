#include <bits/stdc++.h>
 
using namespace std;
 
struct edge {
    int a;
    int b;
    long long w;
    int ind;
};
vector<int> parent;
void initSet(int n){
    parent.resize(n);
    for(int i = 0 ;i < n;i++){
        parent[i] =  i;
    }
}
int findSet(int a){
    return parent[a] = (a == parent[a] ? a : findSet(parent[a]));
}
void unionSet(int a,int b){
    a = findSet(a);
    b = findSet(b);
    parent[b] = a;
}
 
 
 
int main() {
    int n,m;
    long long s;
    ifstream cin("destroy.in");
    ofstream cout("destroy.out");
    cin >> n >> m>> s;
    vector<edge> ed(m);
    for(int i = 0;i < m; i ++){
        int a,b;
        long long c;
        cin >> a>> b >> c;
        ed[i] = {a - 1, b - 1, c, i + 1};
    }
    initSet(n);
    sort(ed.begin(),ed.end(),[](edge a,edge b){
         return a.w > b.w;
 
         });
    vector<bool> used(m, false);
 
 
    for(int i = 0;i < m;i++){
            int a,b;
        a = ed[i].a;
        b = ed[i].b;
        if(findSet(a) != findSet(b)){
            unionSet(a, b);
            used[i] = true;
        }
    }
//    for(auto &i:ed){
//        cout << i.a << " " << i.b<<" " <<i.w<< " " << i.ind <<'\n';
//    }
    long long u  = 0;
    vector<int> ans;
    for(int i = 0;i <m ;i++){
        if(!used[i]){
            u += ed[i].w;
            ans.push_back(i);
        }
    }
    sort(ans.begin(),ans.end(),[&](int a,int b){return ed[a].w > ed[b].w;});
    auto i = ans.begin();
    for(;i != ans.end() && u > s;i++){
        u -= ed[*i].w;
    }
    set<int> res;
    while(i != ans.end()){
        res.emplace(ed[*i].ind);
        i++;
    }
 
 
    cout << res.size() << "\n";
    for(auto &i: res){
        cout << i << " ";
    }
 
 
 
 
 
    return 0;
}
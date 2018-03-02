#include <bits/stdc++.h>

using namespace std;




vector <pair<int,pair<int,int>>>  v;

vector<int> parent;

void make_set (int u) {
    parent[u] = u;
}

int find_set (int u) {
    return u == parent[u] ? u : parent[u] = find_set (parent[u]);


}

void union_set (int a, int b) {
    a = find_set (a);
    b = find_set (b);
    if (a != b)
        parent[b] = a;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
     ifstream cin("spantree2.in");ofstream cout("spantree2.out");

    int n,m;
    cin>>n>>m;
    int a,b,c;
    parent.resize(n);
    for (int i=0; i<m; i++)
    {
        cin>>a>>b>>c;
        v.push_back(make_pair(c,make_pair(a-1,b-1)));

    }
    int k=0;
    sort(v.begin(),v.end());
    for(int i=0;i<n;i++)
        make_set(i);
    for(int i=0;i<m;i++){
        a=v[i].second.first; b = v[i].second.second;
        c=v[i].first;
        if(find_set(a)!=find_set(b)){
            k+=c;
            union_set(a,b);
        }

    }

    cout<<k;
    return 0;
}

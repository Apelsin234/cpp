#include <bits/stdc++.h>

using namespace std;

    vector<vector<int>> v;
    vector<bool> used;
    vector<int> d;

void bfs(int s){
    d[s] = 0;
    used[s] = true;
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i=0;i<v[u].size();i++){
            if(!used[v[u][i]]){
                used[v[u][i]] = true;
                d[v[u][i]] =  d[u]+1;
                q.push(v[u][i]);
            }

        }
    }





}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
   ifstream cin("pathbge1.in");ofstream cout("pathbge1.out");

    int n,k,m;
    cin>>n>>m;
    int a,b,c;

    v.resize(n);
    used.resize(n,false);
    d.resize(n);
    for (int i=0;i<m;i++) {
        cin>>a>>b;
        v[a-1].push_back(b-1);
        v[b-1].push_back(a-1);

    }
    for(int i=0;i<n;i++)
        if(!used[i])
        bfs(i);
    for(int i=0;i<n;i++){
        cout<<d[i]<<" ";
    }

    return 0;
}

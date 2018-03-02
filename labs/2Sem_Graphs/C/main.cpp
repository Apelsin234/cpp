#include <bits/stdc++.h>

using namespace std;



    vector<vector<int>> v;
    enum ss{WHITE, BLACK, GRAY};
    vector<bool> used;
    vector<ss> use;
    vector<int> d;
    int ti = 0;
    list<int> to;
    bool k = true;


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

void dfs(int u) {
    ti++;
    d[u]=ti;
    use[u] = GRAY;
    for(int i=0;i<v[u].size();i++){
            if(use[v[u][i]]==GRAY)
            k=false;
            if(use[v[u][i]]==WHITE)
            dfs(v[u][i]);

    }
    use[u]=BLACK;
    ti++;
    d[u]=ti;
    to.push_front(u);



}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
   ifstream cin("topsort.in");ofstream cout("topsort.out");

    int n,m;
    cin>>n>>m;
    int a,b,c;

    v.resize(n);
    use.resize(n,WHITE);
    d.resize(n);
    for (int i=0;i<m;i++) {
        cin>>a>>b;
        v[a-1].push_back(b-1);

    }
    for(int i=0;i<n;i++)
        {
            if(use[i]==WHITE)
                dfs(i);
        }
    if(k)
    for(list<int>::iterator i = to.begin();i!=to.end();++i){
        cout<<*i + 1<<" ";
    }
    else {
        cout<<-1;
    }

    return 0;
}

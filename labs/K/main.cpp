#include <bits/stdc++.h>

using namespace std;


vector <vector<pair<int,int>>>  v;

enum ss {WHITE, BLACK, GRAY};
vector<ss> use;
vector<int> d;
list<int> to;
bool k = true;

void dfs(int u)
{
    use[u] = GRAY;
    for(int i=0; i<v[u].size(); i++)
    {
        int mid = v[u][i].first;
        if(use[mid]==WHITE)
            dfs(mid);

    }
    to.push_front(u);



}

void dfs2(int u)
{
    use[u] = GRAY;
    for(int i=0; i<v[u].size(); i++)
    {
        int mid = v[u][i].first;
        if(use[mid]==WHITE)
            dfs(mid);

    }



}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ifstream cin("shortpath.in");ofstream cout("shortpath.out");

    int n,k,s,t,m;
    cin>>n>>m>>s>>t;
    int a,b,c;

    v.resize(n);
    use.resize(n,WHITE);
    d.resize(n,100000001);
    for (int i=0; i<m; i++)
    {
        cin>>a>>b>>c;
        v[a-1].push_back(make_pair(b-1,c));

    }
    for(int i=0; i<n; i++)
    {
        if(use[i]==WHITE)
            dfs(i);
    }
    int i = 0;
    int q = false,w;

    use.assign(n, WHITE);

    dfs2(s-1);

    for(list<int>::iterator i = to.begin();i!=to.end();++i){
            if(*i==s-1){
            q=true;
            d[*i]=0;}
        if(!q ){
           continue;
        }
        if(use[*i]==GRAY)
        for(int j=0;j<v[*i].size();j++){
            b = v[*i][j].first;
            c = v[*i][j].second;
            d[b]=min(d[b],d[*i]+c);
        }


    }

    if(d[t-1]!=100000001&&use[t-1]==GRAY)
        cout<<d[t-1];
    else cout<<"Unreachable";
    return 0;
}

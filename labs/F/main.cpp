#include <bits/stdc++.h>

using namespace std;




vector<vector<int>> v_tra;
vector<vector<int>> v;
vector<bool> use;
vector<int> ans;
int ti = 0;
list<int> to;
bool k = true;

void dfs(int u)
{
    use[u] = true;
    for(int i=0; i<v[u].size(); i++)
    {
        if(use[v[u][i]]==false){
            dfs(v[u][i]);
        }
    }
    to.push_front(u);



}

void dfs_tra(int u,int met)
{
    use[u] = true;
    ans[u] = met;
    for(int i=0; i<v_tra[u].size(); i++)
    {
        if(use[v_tra[u][i]]==false){
            dfs_tra(v_tra[u][i], met);
        //else if(ans[v_tra[u][i]]!=met){ti++;k=false;}

    }




}}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
   ifstream cin("cond.in");ofstream cout("cond.out");

    int n,m;
    cin>>n>>m;
    int a,b;

    v.resize(n);
    v_tra.resize(n);
    ans.resize(n);
    use.resize(n,false);
    for (int i=0; i<m; i++)
    {
        cin>>a>>b;
        v[a-1].push_back(b-1);
        v_tra[b-1].push_back(a-1);

    }
    for(int i=0; i<n; i++)
    {
        if(use[i]==false)
            dfs(i);
    }
    use.assign(n,false);
    int met = 1;
    for(list<int>::iterator i = to.begin();i!=to.end();++i)
    {
       if(use[(*i)]==false)
        {
            dfs_tra((*i),met);
            met++;
        }
    }
    met--;
    vector<vector<bool>> ms(met ,vector<bool>(met,false));
    for(int i=0;i<met;i++)
        ms[i][i]=true;
    for(int i=0;i<v.size();i++){
        for(int j=0;j<v[i].size();j++)
        if(ms[ans[i]-1][ans[v[i][j]]-1] == false){
                ms[ans[i]-1][ans[v[i][j]]-1]=true;
                //ms[ans[v[i][j]]-1][ans[i]-1]=1;
        ti++;}}

    cout<<met <<" "<<ti;

    return 0;
}

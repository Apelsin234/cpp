#include <bits/stdc++.h>

using namespace std;




vector<vector<int>> v_tra;
vector<vector<int>> v;
enum ss {WHITE, BLACK, GRAY};
vector<bool> used;
vector<ss> use;
vector<int> d;
vector<int> ans;
int ti = 0;
list<int> to;
bool k = true;

void dfs(int u)
{
    use[u] = GRAY;
    for(int i=0; i<v[u].size(); i++)
    {
        if(use[v[u][i]]==WHITE)
            dfs(v[u][i]);
    }
    to.push_front(u);



}

void dfs_tra(int u,int met)
{
    use[u] = GRAY;
    ans[u] = met;
    for(int i=0; i<v_tra[u].size(); i++)
    {
        if(use[v_tra[u][i]]==WHITE)
            dfs_tra(v_tra[u][i], met);
    }




}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ifstream cin("strong.in");ofstream cout("strong.out");

    int n,m;
    cin>>n>>m;
    int a,b;

    v.resize(n);
    v_tra.resize(n);
    ans.resize(n);
    use.resize(n,WHITE);
    d.resize(n);
    for (int i=0; i<m; i++)
    {
        cin>>a>>b;
        v[a-1].push_back(b-1);
        v_tra[b-1].push_back(a-1);

    }
    for(int i=0; i<n; i++)
    {
        if(use[i]==WHITE)
            dfs(i);
    }
    use.assign(n,WHITE);
    int met = 1;
    for(list<int>::iterator i = to.begin();i!=to.end();++i)
    {
       if(use[(*i)]==WHITE)
        {
            dfs_tra((*i),met);
            met++;
        }
    }
    cout<<met-1<<endl;
    for(int i=0; i<n; i++)
        cout<< ans[i]<< " ";


    return 0;
}

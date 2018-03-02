#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> v;
enum ss {WHITE, BLACK, GRAY};
vector<ss> use;
vector<int> ans;
vector<int> tin ;
vector<int> fup ;
map<pair<int,int>,int> alf;

vector<int> tout ;
int ti = 0;
bool k = true;

void dfs(int u, int p)
{
    ti++;
    tin[u]=ti;
    fup[u]=tin[u];
    use[u] = GRAY;
    for(int i=0; i<v[u].size(); i++)
    {
        if (v[u][i] == p)  continue;
        if(use[v[u][i]]==WHITE)
        {
            dfs(v[u][i],u);
            fup[u] = min (fup[u], fup[v[u][i]]);
            if (fup[v[u][i]] > tin[u])
                ans.push_back(alf[make_pair(u,v[u][i])]);


            }
        else
        {
            fup[u] = min (fup[u], fup[v[u][i]]);
        }

    }
    use[u]=BLACK;
    ti++;
    tout[u]=ti;



}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ifstream cin("bridges.in");ofstream cout("bridges.out");

    int n,m;
    cin>>n>>m;
    int a,b;

    v.resize(n);
    tin.resize(n);
    tout.resize(n);
    fup.resize(n);
    use.resize(n,WHITE);
    for (int i=0; i<m; i++)
    {
        cin>>a>>b;
        v[a-1].push_back(b-1);
        v[b-1].push_back(a-1);
        alf.emplace(make_pair(a-1,b-1),i+1);
        alf.emplace(make_pair(b-1,a-1),i+1);

    }
    for(int i=0; i<n; i++)
    {
        if(use[i] == WHITE)
            dfs(i,-1);
    }
    cout<< ans.size()<<endl;
    sort(ans.begin(),ans.end());
    for(int i=0; i<ans.size(); i++)
    {
        cout<<ans[i]<<" ";
    }

    return 0;
}

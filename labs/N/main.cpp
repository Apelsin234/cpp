#include <bits/stdc++.h>

using namespace std;




vector<vector<int>> v_tra;
vector<vector<int>> v;
enum ss {WHITE, BLACK, GRAY};
vector<ss> use;
vector<int> ans;
list<int> to;

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
    ans[u] = met;
    use[u]=GRAY;
    for(int i=0; i<v_tra[u].size(); i++)
    {
        if(use[v_tra[u][i]]==WHITE)
            dfs_tra(v_tra[u][i], met);
    }
}
int convert(int i)
    {

        return i>=0 ? 2*(i-1) :2*i*(-1) -1;
    }

int  main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    //ifstream cin("transport.in");ofstream cout("transport.out");
    int n;
    int m;
    cin>>n>>m;
    use.resize(2*n,WHITE);
    v.resize(2*n);
    ans.resize(2*n, -5);
    v_tra.resize(2*n);
    map<string,int> otv;
    string otv2[n];
    string s,a,b,c;
    for(int i=0;i<n;i++){
        cin>>s;
        otv["+"+s]=convert(i+1);
        otv2[i]=s;
        otv["-"+s]=convert(-1*(i+1));
    }
    //for(map<string,int>::iterator i = otv.begin();i!=otv.end();++i){
    //    cout<<i->first << " : " <<i->second<<endl;
  //  }

    for(int i =0;i<m;i++){
        cin>>a>>b>>c;
        v[otv[a]].push_back(otv[c]);
        v[(otv[c])^1].push_back((otv[a])^1);
        v_tra[otv[c]].push_back(otv[a]);
        v_tra[(otv[a])^1].push_back((otv[c])^1);
    }

    for (int i=0; i<2*n; ++i)
        if (!use[i])
            dfs(i);
    int met = 0;
    use.assign(2*n,WHITE);
    for(list<int>::iterator i = to.begin();i!=to.end();++i) {
        if (use[*i] == WHITE)
            dfs_tra (*i, met++);
    }
    for (int i=0; i<2*n; i+=2)
        if (ans[i] == ans[i^1]) {
            cout<< -1;
            return 0;
        }
        int answer[n]={};
        int k=0;
    for (int i=0; i<2*n; i+=2) {
        if(ans[i] > ans[i^1]){
                k++;
        answer[i/2]=1;}
    }
    cout<<k<<endl;
    for(int i=0;i<n;i++){
        if(answer[i]==1){
            cout<<otv2[i]<<endl;
        }
    }

    return 0;
}

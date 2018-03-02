#include <bits/stdc++.h>

using namespace std;



    vector<vector<int>> v;
    vector<vector<int>> v_tra;
    vector<int> use;
    enum METK{WIN,LOSE};
    vector<METK> met;
    list<int> to;


void dfs(int u) {
    use[u] = true;
    for(int i=0;i<v[u].size();i++){
            if(use[v[u][i]]==false)
            dfs(v[u][i]);

    }
    to.push_back(u);



}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
   ifstream cin("game.in");ofstream cout("game.out");

    int n,m,t;
    cin>>n>>m>>t;
    int a,b;

    v.resize(n);
    v_tra.resize(n);
    met.resize(n,LOSE);
    use.resize(n,false);
    for (int i=0;i<m;i++) {
        cin>>a>>b;
        v[a-1].push_back(b-1);
        v_tra[b-1].push_back(a-1);
        //vec[a-1][b-1]=true;
    }
    for(int i=0;i<n;i++)
        {
            if(use[i]==false)
                dfs(i);
        }
       for(list<int>::iterator i = to.begin();i!=to.end();++i){
        for(int j=0;j<v_tra[*i].size();j++){
            if(met[*i]==LOSE){
                met[v_tra[*i][j]]=WIN;
            }
        }}
    if(met[t-1]==WIN)
        cout<<"First player wins";
    else cout<<"Second player wins";

    return 0;
}

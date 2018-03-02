#include <bits/stdc++.h>

using namespace std;



    vector<vector<int>> v;
    vector<int> use;
    list<int> to;


void dfs(int u) {
    use[u] = true;
    for(int i=0;i<v[u].size();i++){
            if(use[v[u][i]]==false)
            dfs(v[u][i]);

    }
    to.push_front(u);



}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
   ifstream cin("hamiltonian.in");ofstream cout("hamiltonian.out");

    int n,m;
    cin>>n>>m;
    int a,b;

    v.resize(n);
    use.resize(n,false);
    //vector<vector<bool>> vec(n,vector<bool>(n,false));
    set<pair<int,int>> ser;
    for (int i=0;i<m;i++) {
        cin>>a>>b;
        v[a-1].push_back(b-1);
        ser.emplace(make_pair(a-1,b-1));
        //vec[a-1][b-1]=true;
    }
    for(int i=0;i<n;i++)
        {
            if(use[i]==false)
                dfs(i);
        }
        bool k=true;
        list<int>::iterator j=to.begin();++j;
    for(list<int>::iterator i = to.begin();j!=to.end();++i,++j){
        if(ser.count(pair<int,int>(*i,*j))==0)k=false;
    }
    if(k)
        cout<<"YES";
    else cout<<"NO";

    return 0;
}

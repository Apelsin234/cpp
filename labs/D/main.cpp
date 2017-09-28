#include <bits/stdc++.h>

using namespace std;



vector<vector<int>> v;
enum ss {WHITE, BLACK, GRAY};
vector<ss> use;
stack<int> comp;
stack<int> to;
bool k = true;




void dfs(int u)
{
    to.push(u);
    use[u] = GRAY;
    for(int i=0; i<v[u].size(); i++)
    {
        if(use[v[u][i]]==WHITE)
            dfs(v[u][i]);
        else if(k&&use[v[u][i]]==GRAY)
        {
            k=false;
            while(to.top()!=v[u][i]){
                comp.push(to.top());
                to.pop();
            }
            comp.push(to.top());



        }
        if(!k)
            break;

    }
    if(!k)
        return;
    use[u]=BLACK;
        to.pop();
    //to.push_front(u);


}



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
ifstream cin("cycle.in");ofstream cout("cycle.out");

    int n,m;
    cin>>n>>m;
    int a,b;

    v.resize(n);
    use.resize(n,WHITE);
    for (int i=0; i<m; i++)
    {
        cin>>a>>b;
        v[a-1].push_back(b-1);

    }
    for(int i=0; i < n; i++)
    {
        if(use[i]==WHITE)
            dfs(i);
            if(!k)
        break;

    }
    if(k)
    {
        cout<<"NO";
    } else {
        cout<<"YES"<<endl;
        while(!comp.empty()){
            cout<<comp.top() + 1<< " ";
            comp.pop();
        }
    }
    return 0;
}

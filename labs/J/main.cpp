#include <bits/stdc++.h>

using namespace std;

vector <pair<double,pair<long long ,long long >>>  v;
vector <pair<double,pair<long long ,long long >>>  ans;

vector<long long > parent;
vector<double> cole;

double cost_air;

vector<bool> use;

void make_set (long long  u)
{
    parent[u] = u;
    cole[u]=0-cost_air;
}

long long  find_set (long long  u)
{
    return u == parent[u] ? u : parent[u] = find_set (parent[u]);
}

void union_set (long long  a, long long  b)
{
    a = find_set (a);
    b = find_set (b);
    if (a != b){
        parent[b] = a;}
}

long long  pow2(long long  k)
{
    return k*k;
}

int  main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ifstream cin("transport.in");ofstream cout("transport.out");

    long long  n;
    cin>>n;
    long long  x[n],y[n];
    use.resize(n,false);
    double cost;
    parent.resize(n);

    for (long long  i=0; i<n; i++)
    {
        cin>>x[i];
    }
    for (long long  i=0; i<n; i++)
    {
        cin>>y[i];
    }
    cin>>cost;
    cin>>cost_air;
    if(n==1){
        cout<<0;
        return 0;
    }
    cole.resize(n,-cost_air);
    for(long long  i=0;i<n-1;i++){
        for(long long  j=i+1;j<n;j++){
                double c = sqrt(pow2(x[i]-x[j])+pow2(y[i]-y[j]));
            v.push_back(make_pair(c,make_pair(i,j)));
      //    v.push_back(make_pair(c,make_pair(j,i)));
        }
    }
    sort(v.begin(),v.end());

    for(long long  i=0; i<n; i++)
        make_set(i);
    long long  a,b;
    double c;
    double k = 0;
    for(long long  i=0; i<v.size(); i++)
    {
        a=v[i].second.first;
        b = v[i].second.second;
        c=v[i].first*cost;
        if(find_set(a)!=find_set(b))
        {
            k+=c;
            union_set(a,b);
            ans.push_back(make_pair(c,make_pair(a,b)));
        }

    }
     for(long long  i=0; i<n; i++)
        make_set(i);
   //for(int qwer=0;qwer<150;qwer++)
    for(long long  i=0;i<ans.size();i++){
        a = ans[i].second.first;
        b = ans[i].second.second;
        c = ans[i].first;
        if(c>=cost_air){
            if(find_set(a)!=find_set(b)){
                    //if(cole[find_set(a)]<=cole[find_set(b)]+cole[find_set(a)]+c&&cole[find_set(b)]<=cole[find_set(b)]+cole[find_set(a)]+c){

           cole[find_set(a)]=cole[find_set(a)]+cole[find_set(b)]+c;
           union_set(a,b);



        }}else{
            if(find_set(a)!=find_set(b))

        cole[find_set(a)]=max(cole[find_set(a)],cole[find_set(b)]);
        union_set(a,b);
        }
        }
    for(int i=0;i<n;i++){
        if(cole[find_set(i)]>0){
            k-=cole[find_set(i)];
            cole[find_set(i)]=-1;
        }
    }
    cout<<setprecision(20)<<k;
    return 0;
}

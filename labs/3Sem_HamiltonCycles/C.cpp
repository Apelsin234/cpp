#include <bits/stdc++.h>
 
using namespace std;
 
int main()
{
    int n;
    cin>>n;
    vector<int> v(n);
    for(int i = 0;i<n;i++){
        v[i] = i + 1;
    }
    stable_sort(v.begin(),v.end(),[](int a, int b){
        cout<<"1 "<<b<<" "<<a<<endl;
        string s;
        cin>> s;
        return s=="NO";
            });
        cout << "0 ";
    for(int &i: v){
        cout <<i << " ";
    }
    return 0;
}
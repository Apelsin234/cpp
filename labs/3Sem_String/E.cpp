#include <bits/stdc++.h>
 
using namespace std;
vector<int> p;
string s;
 
void prefix(){
    p[0] = 0;
    int k = 0;
    for(int i = 1;i <s.size();i++ ){
        while(k != 0 && s[i] != s[k]){
            k = p[k - 1];
        }
        if(s[i] == s[k])
            k++;
        p[i] = k;
    }
}
 
int main()
{
    cin >> s;
    p.resize(s.size());
    int n = s.size();
    prefix();
    cout << (n % (n - p.back()) ==0 ? (n - p.back()) : n);
    return 0;
}
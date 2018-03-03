#include <bits/stdc++.h>
 
using namespace std;
vector<int> z;
string s;
 
void zFunc(){
    z[0] = -1;
    int l,r;
    l = r = 0;
    for(int i = 1;i < s.size();i++) {
        z[i] = max(0, min(r - i, z[i - l]));
        while(i + z[i] < s.size() && s[i+ z[i]] == s[z[i]]){
            z[i]++;
        }
        if(i + z[i] > r){
            l = i;
            r = i + z[i];
        }
    }
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin >> s;
    z.resize(s.size());
    zFunc();
 
    for(auto &i : z){
        if(i != -1)
        cout << i << " ";
    }
    return 0;
}
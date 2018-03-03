#include <bits/stdc++.h>
 
using namespace std;
vector<int> z;
string s;
string t;
vector<int> res;
 
void zFunc(){
    int ans = t.size();
    z[0] = -1;
    s = t + '#' + s;
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
        if(z[i] == ans){
                res.push_back(i - ans);
        }
    }
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin >> t;
    cin >> s;
    z.resize(t.size() + 1 +s.size());
    zFunc();
    cout << res.size() << "\n";
    for(auto &i : res){
        cout << i << " ";
    }
    return 0;
}
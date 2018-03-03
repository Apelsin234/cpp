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
 
bool comp(int a, int b, const string & s){
    int n = s.size();
    while(a < n && b < n && s[a] == s[b]){
        a++;
        b++;
    }
    if(a == n){
        return true;
    }
    if(b == n){
        return false;
    }
    return s[a] < s[b];
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ifstream cin("cyclic.in");
    ofstream cout("cyclic.out");
    cin >> s;
    int n = s.size();
    s = s + s;
    z.resize(s.size());
    zFunc();
    int k = 0;
    for(int i =1; i < n;i++){
        if(z[i]< n && s[z[i] + i] < s[z[i]]){
            k++;
        }
    }
    cout << k  + 1;
    return 0;
}
#include <bits/stdc++.h>
 
using namespace std;
 
string s;
 
vector<long long> pow_p;
 
vector<long long> h;
 
void pre(){
    const long long p = 31;
    pow_p[0] = 1;
    for(int i = 1;i< s.size();i++){
        pow_p[i] = pow_p[i - 1] * p;
    }
    for(int i = 0;i< s.size();i++){
        h[i] = (s[i] - 'a' + 1) * pow_p[i] + (i ? h[i-1] : 0);
    }
}
 
bool check(int a, int b, int c ,int d){
    if(a == c && b == d){
        return true;
    }
    if(b - a != d - c){
        return false;
    }
    long long h1 = h[b];
    if(a)h1 -= h[a - 1];
    long long h2 = h[d];
    if(c)h2 -= h[c - 1];
    if(a < c && h1 * pow_p[c - a] == h2 || c < a && h2 * pow_p[a - c] == h1){
        return true;
    } else {
        return false;
    }
 
}
 
int main()
{
    cin >> s;
    h.resize(s.size());
    pow_p.resize(s.size());
    pre();
    int m;
    cin>> m;
    while(m--) {
        int a, b, c, d;
        cin >> a>> b>> c >>d;
        cout << (check(a - 1, b - 1, c - 1, d - 1) ? "Yes\n": "No\n");
 
    }
    return 0;
}
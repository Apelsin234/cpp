#include <bits/stdc++.h>
 
using namespace std;
 
vector<int> t;
vector<int> q;
 
void build() {
  for (int i = (t.size() >> 1 ) - 1; i > 0; --i) t[i] = min(t[i<<1], t[i<<1|1]);
}
 
int query(int l, int r) {
  int resl = 1000000000;
  int resr = 1000000000;
  for (l += (t.size() >> 1 ), r += (t.size() >> 1); l < r; l >>= 1, r >>= 1) {
    if (l&1) resl = min (resl, t[l++]);
    if (r&1) resr = min ( t[--r], resr);
  }
  return min(resl,resr);
}
 
vector<int> compactArray(string& v) {
    string input= v;
    sort(input.begin(), input.end());
    input.resize(unique(input.begin(), input.end()) - input.begin());
    unordered_map<int, int> mapping;
    for (int i = 0 ; i < input.size() ; i++)
        mapping[input[i]] = i;
    vector<int> result(v.size());
    for (int i = 0 ; i < v.size() ; i++)
        result[i] = mapping[v[i]];
    return result;
}
 
 
vector<int> calcSuffixArray(string a) {
    auto s = compactArray(a);
 
    int n = s.size();
    vector<int> p(n);
    vector<int> cnt(n);
    vector<int> c(n);
 
    for (auto &i: s)
        ++cnt[i];
    for (int i=1; i<n; ++i)
        cnt[i] += cnt[i-1];
    for (int i=0; i<n; ++i)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classN = 1;
    for (int i=1; i<n; ++i) {
        if (s[p[i]] != s[p[i-1]])  ++classN;
        c[p[i]] = classN-1;
    }
 
    vector<int> pn(n);
    vector<int> cn(n);
    for (int h=1; h<n; h <<= 1) {
        for (int i=0; i<n; ++i) {
            pn[i] = p[i] - h;
            if (pn[i] < 0)  pn[i] += n;
        }
        cnt.assign(classN, 0);
        for (auto &i: pn)
            ++cnt[c[i]];
        for (int i=1; i<classN; ++i)
            cnt[i] += cnt[i-1];
        for (int i=n-1; i>=0; --i)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classN = 1;
        for (int i=1; i<n; ++i) {
            int mid1 = (p[i] + h) % n;
            int mid2 = (p[i-1] + h) % n;
            if (c[p[i]] != c[p[i-1]] || c[mid1] != c[mid2])
                ++classN;
            cn[p[i]] = classN-1;
        }
        c = cn;
    }
 
    return p;
}
vector<int>lcp;
void kasai(const string &s,const vector<int> &suf){
    int n = s.size();
    int k=0;
    lcp.resize(n, 0);
    int rank[n] = {};
 
    for(int i=0; i<n; i++)
        rank[suf[i]] = i;
    for(int i=0; i<n; i++,  k?k--:0)
    {
        if(rank[i]==n-1) {
            k=0;
            continue;
    }
        int j = suf[rank[i]+1];
        while(i+k<n && j+k<n && s[i+k]==s[j+k])
            k++;
        lcp[rank[i]]=k;
    }
}
 
string findCommonSubstring(string s,vector<int> &suf, int m){
    int l=0,r =0;
    int n = suf.size();
    int k = 0;
    vector<int> cnt(m,0);
    int u = (1<<m) - 1;
    string ans = "";
    while(r < n){
        while(r < n && k != u){
                int y = -1;
            for(int i = 0;i <m;i++){
                if(suf[r] < q[i]){
                    y = i;
                    break;
                }
            }
            cnt[y]++;
            k |= (1 << y);
            r++;
        }
        while(k == u){
            int qw= query(l , r - 1);
           if(qw > ans.size() ){
                ans = s.substr(suf[l +1], qw);
           }
            int y = -1;
            for(int i = 0;i <m;i++){
                if(suf[l] < q[i]){
                    y = i;
                    break;
                }
            }
            cnt[y]--;
            if(cnt[y] == 0)
            k -= (1 << y);
            l++;
        }
    }
    return ans;
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ifstream cin("common.in");
    ofstream cout("common.out");
    int m = 2;
   // cin >> m;
    string s;
    q.resize(m);
    for(int i = 0;i < m;i++){
    string t;
    cin >> t;
    s += t;
    s.push_back(i);
    q[i] = s.size();
    }
    vector<int> suf = calcSuffixArray(s);
    kasai(s, suf);
    t.resize(2 * (lcp.size() - 1));
    for(int i = 0;i < (int)lcp.size() - 1 ;i++){
        t[lcp.size() + i - 1] = lcp[i];
    }
    build();
    auto a = findCommonSubstring(s, suf, m);
    cout << a;
    return 0;
}
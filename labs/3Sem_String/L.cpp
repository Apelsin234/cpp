#include <bits/stdc++.h>
 
using namespace std;
 
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
 
    vector<int> c;
    int classN = -1;
 
vector<int> calcSuffixArray(string a) {
    auto s = compactArray(a);
    int n = s.size();
    vector<int> p(n);
    vector<int> cnt(n);
    c.resize(n);
    for (auto &i: s)
        ++cnt[i];
    for (int i=1; i<n; ++i)
        cnt[i] += cnt[i-1];
    for (int i=0; i<n; ++i)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    classN = 1;
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
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
   ifstream cin("shifts.in");
   ofstream cout("shifts.out");
    string s;
    cin >> s;
    auto suf = calcSuffixArray(s);
    //kasai(s, suf);
 
 
    int n;
    cin >> n;
    //cout << classN << endl;
    if(classN >= n){
            int i = 0;
        for(;c[i]!=n- 1;i++){}
        cout << s.substr(i) + s.substr(0, i);
    }else {
        cout << "IMPOSSIBLE";
    }
 
 
 
    return 0;
}
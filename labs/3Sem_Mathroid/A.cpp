#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    ifstream cin("schedule.in");ofstream cout("schedule.out");
    int n;
    cin >> n;
 
    long long ans = 0;
    vector<pair<int,long long> > v(n);
    for(auto &i: v){
        int a,b;
        cin >> a >> b;
        i = {a, b};
        ans += b;
    }
    //sort(v.begin(), v.end(), [](pair<int,int> a, pair<int,int> b){return a.second > b.second;});
    set<int> num;
    sort(v.begin(), v.end());
//    for(auto &i: v){
//        cout << i.first << " " << i.second << endl;
//    }
    int k = 0;
    for(int i = 0 ; i < n; i++){
        num.insert(v[i].second);
 
            ans -= v[i].second;
        if(v[i].first > k) {
            k++;
        }else {
            ans += *(num.begin());
            num.erase(num.begin());
        }
    }
 
    cout << ans;
 
 
    return 0;
}
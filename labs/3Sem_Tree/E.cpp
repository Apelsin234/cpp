#include <iostream>
#include <vector>
#include <bitset>
 
using namespace std;
vector<vector<int> > v;
vector<int> answer;
 
bitset<300004> used(0);
int dfs(int u, int& k, int si, int p = -1) {
    int res = 0;
    for (int &to: v[u]) {
        if (to != p && !used[to])
            res += dfs(to, k, si, u) ;
    }
    res++;
    if (res << 1 >= si || p == -1)
        k =  (k == -1) ? u : k;
    return res;
}
void recursive(int si, int u = 0, int k = -1) {
    int p = -1;
    dfs(u, p, si);
    used[p] = 1;
    answer[p] = k;
    for (int &to: v[p]) {
        if (!used[to]) {
            recursive( si >> 1, to, p);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    answer.resize(n, 0);
    v.resize(n);
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        v[--a].push_back(--b);
        v[b].push_back(a);
    }
    recursive(n);
    for (int &i: answer) {
        cout << i + 1 << " ";
    }
    return 0;
}
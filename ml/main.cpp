#include <bits/stdc++.h>
#include <string>

using namespace std;

vector<vector<int> > g;
vector<set<int> > total_g;
vector<set<int> > total_g_rev;
vector<vector<int> > g_rev;
int n;
map<pair<int, int>, int> mp_add;
map<pair<int, int>, int> mp_mul;
map<pair<int, int>, int> mp_impl;
map<int, int> mp_ne;
int zero = -1;
int one = -1;

void add_ver() {
    string s;
    for(int i = 0; i < n; i++) {
        getline(cin, s);
        stringstream st;
        st << s;
        int a;

        g[i].push_back(i);
        g_rev[i].push_back(i);
        while (st >> a) {
            a--;
            g[i].push_back(a);
            g_rev[a].push_back(i);
        }
    }
}

bool check_add_impl(int a, int b) {
    if(mp_add.count({a, b}) != 0) {
        return true;
    }
    set<int> se;
    set<int> a_li = total_g[a];
    set<int> b_li = total_g[b];
//    cout << a << " " << b << " \n";
//    cout << "A_li:\n";
//    for(auto h: a_li) {
//        cout << h << " " ;
//    }
//    cout << endl;
//    cout << "B_li:\n";
//    for(auto h: b_li) {
//        cout << h << " " ;
//    }
//    cout << endl;


    for(auto h: b_li){
            if(a_li.count(h))
            se.emplace(h);
    }
    //se.emplace(b);
    //se.emplace(a);
//    cout << "SE:\n";
//    for(auto h: se) {
//        cout << h << " " ;
//    }
//    cout << endl;

    if(se.empty()){
        return false;
    }
    for(auto i: se) {
        set<int> eps;
        for(auto h: se){
            if(total_g[i].count(h))
            eps.emplace(h);
        }
//
//        cout << "Eps:\n";
//    for(auto h: eps) {
//        cout << h << " " ;
//    }
//    cout << endl;
        if(eps.size() == se.size()) {
            mp_add[{a, b}] = mp_add[{b, a}] = i;
            return true;
        }
    }
    return false;

}
bool check_mul_impl(int a, int b) {
    if(mp_mul.count({a, b}) != 0) {
        return true;
    }
     set<int> se;
    set<int> a_li = total_g_rev[a];
    set<int> b_li = total_g_rev[b];

    for(auto h: b_li){
            if(a_li.count(h))
            se.emplace(h);
    }
    if(se.empty()){
        return false;
    }
    for(auto i: se) {
        set<int> eps;
        for(auto h: se){
            if(total_g_rev[i].count(h))
            eps.emplace(h);
        }
        if(eps.size() == se.size()) {
            mp_mul[{a, b}] = mp_mul[{b, a}] = i;
            return true;
        }
    }
    return false;

}

pair<int,int> check_add() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (!check_add_impl(i, j)) {
                return {i + 1 , j + 1};
            }
        }
    }
    return {-1, -1};
}


pair<int,int> check_mul() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (!check_mul_impl(i, j)) {
                return {i + 1, j + 1};
            }
        }
    }
    return {-1, -1};
}
tuple<int,int, int> check_distr() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                if(mp_mul[{i, mp_add[{j, k}]}] != mp_add[{mp_mul[{i, j}], mp_mul[{i, k}]}]) {
                    return tuple<int,int,int>(i + 1, j + 1, k + 1);
                }
            }
        }
    }
    return tuple<int,int,int>(-1, -1, -1);
}

int check_bool() {

    for(int i = 0; i < n; i++) {
        mp_ne[i] = mp_impl[{i, zero}];
        if(one != mp_add[{i, mp_ne[i]}]) {
            return i + 1;
        }
    }
    return -1;
}

void impl() {
    for(int i = 0; i < n; i++) {
        for(int j = 0 ; j < n; j++) {
            int mini = -1;
            for(auto k = mp_mul.find({i,0}); k != mp_mul.upper_bound({i, n - 1}); k++) {
                if(mini == -1 ){
                    if(total_g_rev[j].count(k->second)) {
                        mini = k->first.second;
                    }
                } else {
                    int ry = k->first.second;
                   if(total_g_rev[j].count(k->second) != 0 && total_g_rev[ry].count(mini) != 0) {
                        mini = ry;
                    }
                }
            }

            mp_impl[{i, j}] =mini;
            //cout << mini << endl;
        }
    }
}
void find_zero() {
    int o = 0;
    for(auto i: total_g){

        if(i.size() == n) {
            zero = o;
            return ;
        }
    o++;
    }
}
void find_one() {
    int o = 0;
    for(auto i: total_g_rev){

        if(i.size() == n) {
            one = o;
            return ;
        }
    o++;
    }
}

void make_total(){
   for(int cur = 0;cur < n;cur++) {

    function<void (int)> func = [&](int i){

        total_g[cur].insert(g[i].begin(), g[i].end());
        for(auto j: g[i]) {
            if(j != i) {
                func(j);
            }
        }
    };
        func(cur);
   }
}

void make_total_rev(){
   for(int cur = 0;cur < n;cur++) {

    function<void (int)> func = [&](int i){

        total_g_rev[cur].insert(g_rev[i].begin(), g_rev[i].end());
        for(auto j: g_rev[i]) {
            if(j != i) {
                func(j);
            }
        }
    };
        func(cur);
   }
}



int main()
{
    setlocale(LC_ALL, "RUS");

//    ifstream cin("input.txt");
  //  ofstream cout("output.txt");
    string s;
    stringstream str;
    getline(cin, s);
    str << s;
    str >> n;

    g.resize(n);
    g_rev.resize(n);
    total_g_rev.resize(n);
    total_g.resize(n);
    add_ver();

//    cout << "A\n";
    make_total();
    make_total_rev();
//    for(auto i: total_g) {
//        for(auto j: i) {
//            cout << j << " ";
//        }
//        cout << endl;
//    }

   // cout << "B\n";
    int a, b, c;
    tie(a, b) = check_add();
    if (a != -1) {
        printf("Операция '+' не определена: %d+%d    ", a, b);
        return 0;
    }
    //cout << "C\n";

    tie(a, b) = check_mul();
    if (a != -1) {
        printf("Операция '*' не определена: %d*%d   ", a, b);
        return 0;
    }

   // cout << "D\n";

    tie(a, b, c) = check_distr();
    if(c != -1) {

        printf("Нарушается дистрибутивность: %d*(%d+%d)   ", a, b, c);
        return 0;
    }
    impl();
    find_zero();
    find_one();
    a = check_bool();
    if(a != -1) {
        printf("Не булева алгебра: %d+~%d   ", a, a);
        return 0;

    }
    cout << "Булева алгебра   ";

    return 0;
}

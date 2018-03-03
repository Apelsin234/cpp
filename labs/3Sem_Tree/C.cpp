#include <bits/stdc++.h>
using namespace std;
 
struct Node;
 
vector<Node*> nodes;
 
struct Node{
        Node *left = nullptr, *right = nullptr, *parent = nullptr, *link = nullptr;
        int size = 1;
        bool rev = false;
        Node(){
        left = right = parent = link = nullptr;
        size = 1;
        rev = false;
        }
 
};
 
int size(Node *x){
    return (x ? x->size : 0);
}
 
void recomp(Node *x){
    x->size = 1 + size(x->left) + size(x->right);
}
 
void set_parent(Node *c, Node *p){
    if(c){
        c->parent = p;
    }
}
 
void reverse(Node *x){
    if(x)
        x->rev ^= true;
}
 
void push(Node *x){
    if( x && x->rev) {
        swap(x->right, x->left);
        x->rev = false;
        reverse(x->left);
        reverse(x->right);
    }
}
 
void keep_parent(Node *x) {
set_parent(x->left, x);
set_parent(x->right, x);
recomp(x);
 
}
 
void rot(Node *p, Node *c) {
    auto gp = p->parent;
    if(gp ){
        if(gp->left == p){
            gp->left = c;
        } else {
            gp->right = c;
        }
    }
    if(p->left == c){
        p->left = c->right;
        c->right = p;
    } else {
        p->right = c-> left;
        c->left = p;
    }
    keep_parent(p);
    keep_parent(c);
    c->parent = gp;
 
 
}
 
Node *splay(Node *x) {
    if(!x->parent){
        return x;
    }
    auto p = x->parent;
    auto gp = p->parent;
    if(!gp){
        rot(p, x);
        return x;
    }
    if((gp->left == p) == (p->left == x)){
        rot(gp, p);
        rot(p, x);
    } else {
        rot(p, x);
        rot(gp, x);
    }
    return splay(x);
}
 
Node *find(Node * x, int key){
    if(!x)
        return x;
    push(x);
    int th = size(x->left);
    if(key == th) {
        return splay(x);
 
    }
    if(key < th && x->left)
        return find(x->left, key);
    if(key > th && x->right){
        return find(x->right, key - th - 1);
    }
    return splay(x);
 
}
 
pair<Node*,Node*> split(Node *root, int key){
    if(!root){
        return {root, root};
    }
    root = find(root, key);
    if(root->size <= key) {
        return {root, nullptr};
    }
    set_parent(root->left, nullptr);
 
    root->left = nullptr;
    recomp(root);
    return {root->left, root};
}
 
Node * merge(Node *l,Node *r){
    if(!r)
        return l;
    if(!l)
        return r;
    r =find(r, 0);
    r->left = l;
    keep_parent(r);
    return r;
}
 
void cleanup(Node *x){
    if(!x)
        return;
    cleanup(x->parent);
    push(x);
}
 
Node * supportRoot(Node *x){
    cleanup(x);
    return splay(x);
}
 
Node *cutout(Node * x){
    supportRoot(x);
    Node *l,  *r;
    tie(l, r) = split(x, size(x->left) + 1);
    if(r)
        find(r, 0)->link = x;
    return x;
}
 
Node *expose(Node *x){
    x = find(cutout(x), 0);
    while(x->link){
        auto nxt = cutout(x->link);
        x->link = nullptr;
        x = find(merge(nxt, x), 0);
    }
    return x;
 
}
 
int depth(Node *x){
    expose(x);
    return supportRoot(x)->size - 1;
}
 
Node *link(Node *c, Node *p){
    c->link = p;
    return expose(c);
}
Node *cut(Node *x, Node *p){
    expose(p);
    x->link = nullptr;
}
 
Node* find_root(Node* x){
    return expose(x);
}
 
void revert(Node *x){
    auto r = expose(x);
    reverse(supportRoot(r));
}
 
int dist(Node *u, Node *v){
    revert(u);
    auto w = expose(v);
    if (w != u){
        return -1;
    }
    return depth(v);
}
 
void add(Node *u, Node *v){
    revert(u);
    link(u, v);
}
 
void rem(Node *u, Node *v){
    revert(v);
    cut(u, v);
    }
 
 
int main() {
 
 
    int n, m;
    cin >> n >> m;
    nodes.resize(n);
    for(int i = 0;i < n;i++){
        nodes[i] = new Node();
    }
 
 
    for(int i = 0 ;i < m; i++){
        string s;
        int a, b;
        cin >> s >> a >> b;
        a--;
        b--;
        if(s == "link"){
            add(nodes[a], nodes[b]);
        }else
        if(s == "cut"){
            rem(nodes[a],nodes[b]);
 
        } else {
            if(find_root(nodes[a]) == find_root(nodes[b])){
                cout << 1 << endl;
                continue;
            }
            cout << 0 << endl;
        }
    }
    for(int i = 0 ;i < n; i++){
        delete nodes[i];
    }
    return 0;
}
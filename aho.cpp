#include <bits/stdc++.h>
 
struct Node {
    bool terminal;
    Node *ptr[2];
    Node *fail;
    int color;
    int d;
 
    Node() : d(0), color(0), fail(NULL), terminal(false) { ptr[0] = ptr[1] = NULL; }
 
    ~Node() {
        for (int i = 0; i < 2; i++)
            if (ptr[i] && ptr[i]->d > d)
                delete ptr[i];
    }
};
 
void add(Node *root, std::string &s) {
    Node *temp = root;
    for (int i = 0; i < s.length(); i++) {
        int c = s[i] - '0';
        if (!temp->ptr[c])
            temp->ptr[c] = new Node();
        temp = temp->ptr[c];
    }
    temp->terminal = true;
}
 
void find_fail(Node *root) {
    std::queue<Node*> q;
    for (int i = 0; i < 2; i++)
        if (!root->ptr[i])
            root->ptr[i] = root;
        else {
            root->ptr[i]->fail = root;
            q.push(root->ptr[i]);
        }
 
    while (!q.empty()) {
        Node *v = q.front();
        q.pop();
        for (int i = 0; i < 2; i++) {
            Node *u = v->ptr[i];
            if (u) {
                q.push(u);
 
                Node *x = v->fail;
                while (!x->ptr[i])
                    x = x->fail;
 
                u->fail = x->ptr[i];
                if (u->fail->terminal)
                    u->terminal = true;
            }
        }
    }
}
 
void build_move(Node *root) {
    std::queue<Node*> q;
    q.push(root);
 
    while (!q.empty()) {
        Node *v = q.front();
        q.pop();
        for (int i = 0; i < 2; i++) {
            if (!v->ptr[i])
                v->ptr[i] = v->fail->ptr[i];
            else {
                v->ptr[i]->d = (v->d) + 1;
                q.push(v->ptr[i]);
            }
        }
    }
}
 
bool find_cycle(Node *v) {
    v->color = 1;
    for (int i = 0; i < 2; i++) {
        if (v->ptr[i]->color == 1)
            return true;
        else if (v->ptr[i]->color == 0 && !v->ptr[i]->terminal && find_cycle(v->ptr[i]))
            return true;
    }
    v->color = 2;
    return false;
}
 
void solve() {
    int n;
    std::string s;
    std::cin >> n;
 
    Node *root = new Node();
 
    for (int i = 1; i <= n; i++) {
        std::cin >> s;
        add(root, s);
    }
 
    root->d = 0;
    find_fail(root);
    build_move(root);
 
    std::cout << ((find_cycle(root)) ? "TAK\n" : "NIE\n");
 
    delete root;
}
 
int main() {
    std::ios_base::sync_with_stdio(0); std::cin.tie(NULL);
    int z;
    std::cin >> z;
    while (z--)
        solve();
}
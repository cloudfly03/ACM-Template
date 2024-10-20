#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define ld long double
#define pii pair<int,int>
#define complex complex<ld>
#define rand mt19937_64
#define endl '\n'
#define PI (ld)(3.141592653589793)
#define INF (int)(1e8)
#define MOD (int)(1e8)
#define eps (ld)(1e-9)
#define P (int)(998244353)
#define G (int)(3)
#define mpair(x,y) make_pair(x,y)
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)

#define lc(x) tr[x].s[0]
#define rc(x) tr[x].s[1]

const int N = 1100010;

typedef struct {
    int v;
    int p, s[2];
    int cnt, sz;
    void init(int p1, int v1) {
        p = p1, v = v1;
        cnt = sz = 1;
    }
}SplayTree;
SplayTree tr[N];
int root,cnt;

//修改子树节点数
void pushup(int x) {
    tr[x].sz = tr[lc(x)].sz + tr[rc(x)].sz + tr[x].cnt;
}

//左/右旋操作
void rotate(int x) {
    int y = tr[x].p, z = tr[y].p, k = rc(y) == x;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[y].p = x, tr[x].s[k ^ 1] = y;
    tr[x].p = z, tr[z].s[rc(z) == y] = x;
    pushup(y), pushup(x);
}

//x转为k的子节点
void splay(int x, int k) {
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k) (lc(y) == x) ^ (lc(z) == y) ? rotate(x) : rotate(y);
        rotate(x);
    }
    if (!k) root = x;
}

//找到数值v所在节点，将该节点转到root下
void find(int v) {
    int x = root;
    while (tr[x].s[v > tr[x].v] && tr[x].v != v)
        x = tr[x].s[v > tr[x].v];
    splay(x, 0);
}

// //同时返回前驱/后继节点编号
// pii get(int v) {
//     find(v);
//     pii res = mpair(0, 0);
//     if (v > tr[root].v) res.first = root;
//     if (v < tr[root].v) res.second = root;
//     if (!res.first) {
//         int x = tr[root].s[0];
//         while (tr[x].s[1])x = tr[x].s[1];
//         res.first = x;
//     }
//     if (!res.second) {
//         int x = tr[root].s[1];
//         while (tr[x].s[0])x = tr[x].s[0];
//         res.second = x;
//     }
//     return res;
// }

// // k = 1 计算后继 k = 0 计算前驱
// int get(int v, bool k) {
//     find(v);
//     int x = root;
//     if (k ^ (v > tr[x].v)) return x;
//     x = tr[x].s[k];
//     k ^= 1;
//     while (tr[x].s[k]) x = tr[x].s[k];
//     return x;
// }

//找到前驱节点的编号
int getpre(int v) {
    find(v);
    int x = root;
    if (tr[x].v < v) return x;
    x = lc(x);
    while (rc(x)) x = rc(x);
    splay(x, 0);
    return x;
}

//找到后继节点的编号
int getsuc(int v) {
    find(v);
    int x = root;
    if (tr[x].v > v) return x;
    x = rc(x);
    while (lc(x)) x = lc(x);
    splay(x, 0);
    return x;
}

//删去值为v的节点
void del(int v) {
    int pre = getpre(v);
    int suc = getsuc(v);
    splay(pre, 0), splay(suc, pre);
    int del = tr[suc].s[0];
    if (tr[del].cnt > 1)
        tr[del].cnt--, splay(del, 0);
    else
        tr[suc].s[0] = 0, splay(suc, 0);
}

void insert(int v) {
    int x = root, p = 0;
    while (x && tr[x].v != v)
        p = x, x = tr[x].s[v > tr[x].v];
    if (x) tr[x].cnt++;
    else {
        x = ++cnt;
        if (p) tr[p].s[v > tr[p].v] = x;
        tr[x].init(p, v);
    }
    splay(x, 0);
}

int getrk(int v) {
    insert(v);
    // find(v);
    int res = tr[tr[root].s[0]].sz;
    del(v);
    return res;
}

int getv(int rk) {
    int x = root;
    while (true) {
        if (rk <= tr[lc(x)].sz) x = lc(x);
        else if (rk <= tr[lc(x)].sz + tr[x].cnt) break;
        else rk -= tr[lc(x)].sz + tr[x].cnt, x = rc(x);
    }
    splay(x, 0);
    return tr[x].v;
}

int n;

void solve() {
    cin >> n;
    insert(-INF), insert(INF);
    for (int i = 1;i <= n;++i) {
        int op;cin >> op;
        int x;cin >> x;
        if (op == 1) insert(x);
        else if (op == 2) del(x);
        else if (op == 3) cout << getrk(x) << endl;
        else if (op == 4) cout << getv(x + 1) << endl;
        else if (op == 5) cout << tr[getpre(x)].v << endl;
        else cout << tr[getsuc(x)].v << endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}
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

#define lc(x) tr[x].lc
#define rc(x) tr[x].rc

const int N = 1e5 + 1;

typedef struct {
    int lc, rc;
    int v, k;
    int sz;
}Treap;
Treap tr[N];
int root, cnt;
rand rnd(time(NULL));

int initnode(int v) {
    tr[++cnt].v = v;
    tr[cnt].k = rnd();
    tr[cnt].sz = 1;
    return cnt;
}

void pushup(int x) {
    tr[x].sz = tr[lc(x)].sz + tr[rc(x)].sz + 1;
}

void split(int p, int v, int& x, int& y) {
    if (!p) { x = y = 0; return; }
    if (tr[p].v <= v)
        x = p, split(rc(p), v, rc(x), y);
    else y = p, split(lc(p), v, x, lc(y));
    pushup(p);
}

int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (tr[x].k < tr[y].k) {
        rc(x) = merge(rc(x), y);
        pushup(x);return x;
    }
    else {
        lc(y) = merge(x, lc(y));
        pushup(y);return y;
    }
}

void insert(int v) {
    int x, y;
    split(root, v, x, y);
    x = merge(x, initnode(v));
    root = merge(x, y);
}

void del(int v) {
    int x, y, z;
    split(root, v, x, y);
    split(x, v - 1, x, z);
    z = merge(lc(z), rc(z));
    root = merge(merge(x, z), y);
}

// 获得第rk个点的编号
int getid(int p, int rk) {
    if (rk <= tr[lc(p)].sz)
        return getid(lc(p), rk);
    else if (rk > tr[lc(p)].sz + 1)
        return getid(rc(p), rk - tr[lc(p)].sz - 1);
    else return p;
}

int getpre(int v) {
    int x, y;
    split(root, v - 1, x, y);
    int resid = getid(x, tr[x].sz);
    root = merge(x, y);
    return tr[resid].v;
}

int getsuc(int v) {
    int x, y;
    split(root, v, x, y);
    int resid = getid(y, 1);
    root = merge(x, y);
    return tr[resid].v;
}

int getrk(int v) {
    int x, y;
    split(root, v - 1, x, y);
    int res = tr[x].sz + 1;
    merge(x, y);
    return res;
}

int getv(int rk) {
    return tr[getid(root, rk)].v;
}

int n;

void solve() {
    cin >> n;
    for (int i = 1;i <= n;++i) {
        int op, x;cin >> op >> x;
        if (op == 1) insert(x);
        else if (op == 2) del(x);
        else if (op == 3) cout << getrk(x) << endl;
        else if (op == 4) cout << getv(x) << endl;
        else if (op == 5) cout << getpre(x) << endl;
        else cout << getsuc(x) << endl;
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
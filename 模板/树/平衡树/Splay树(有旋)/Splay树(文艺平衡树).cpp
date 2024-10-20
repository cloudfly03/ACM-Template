#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define ld long double
#define pii pair<int,int>
#define mpair(x,y) make_pair(x,y)
#define complex complex<ld>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define PI (ld)(3.141592653589793)
#define INF (int)(1e8)
#define MOD (int)(1e8)
#define eps (ld)(1e-9)
#define P (int)(998244353)
#define G (int)(3)

#define lc(x) tr[x].s[0]
#define rc(x) tr[x].s[1]

const int N = 1e6 + 1;

typedef struct {
    int v;
    int p, s[2];
    int sz;
    bool lag;
    void init(int p1, int v1) {
        p = p1, v = v1, sz = 1;
    }
}SplayTree;
SplayTree tr[N];
int root;
int cnt;

void pushup(int x) {
    tr[x].sz = tr[lc(x)].sz + tr[rc(x)].sz + 1;
}

void pushdown(int x) {
    if (tr[x].lag) {
        swap(lc(x), rc(x));
        tr[lc(x)].lag ^= 1;
        tr[rc(x)].lag ^= 1;
        tr[x].lag = 0;
    }
}

void rotate(int x) {
    int y = tr[x].p, z = tr[y].p, k = rc(y) == x;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[y].p = x, tr[x].s[k ^ 1] = y;
    tr[x].p = z, tr[z].s[rc(z) == y] = x;
    pushup(y), pushup(x);
}

void splay(int x, int k) {
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k) (lc(y) == x) ^ (lc(z) == y) ? rotate(x) : rotate(y);
        rotate(x);
    }
    if (!k) root = x;
}

void insert(int v) {
    int x = root, p = 0;
    while (x) p = x, x = tr[x].s[v > tr[x].v];
    x = ++cnt;
    if (p) tr[p].s[v > tr[p].v] = x;
    tr[x].init(p, v);
    splay(x, 0);
}

int getv(int rk) {
    int x = root;
    while (true) {
        pushdown(x);
        if (rk <= tr[lc(x)].sz) x = lc(x);
        else if (rk <= tr[lc(x)].sz + 1) break;
        else rk -= tr[lc(x)].sz + 1, x = rc(x);
    }
    splay(x, 0);
    return x;
}

int n, m;

void dfs(int p) {
    pushdown(p);
    if (lc(p)) dfs(lc(p));
    if (tr[p].v >= 1 && tr[p].v <= n)
        cout << tr[p].v << ' ';
    if (rc(p)) dfs(rc(p));
}

void solve() {
    insert(-INF), insert(INF);
    cin >> n >> m;
    for (int i = 1;i <= n;++i) insert(i);

    for (int i = 1;i <= m;++i) {
        int l, r;cin >> l >> r;
        l = getv(l), r = getv(r + 2);
        splay(l, 0);splay(r, l);
        tr[lc(r)].lag ^= 1;
    }
    dfs(root);
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
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
    int lag;
}Treap;
Treap tr[N];
int root, cnt;
rand rnd(clock());

int initnode(int v) {
    tr[++cnt].v = v;
    tr[cnt].k = rnd();
    tr[cnt].sz = 1;
    return cnt;
}

void pushup(int x) {
    tr[x].sz = tr[lc(x)].sz + tr[rc(x)].sz + 1;
}

void pushdown(int x) {
    if (!tr[x].lag) return;
    swap(lc(x), rc(x));
    tr[lc(x)].lag ^= 1;
    tr[rc(x)].lag ^= 1;
    tr[x].lag = 0;
}

void split(int p, int sz, int& x, int& y) {
    if (!p) { x = y = 0; return; }
    pushdown(p);
    if (tr[lc(p)].sz < sz)
        x = p, split(rc(p), sz - tr[lc(p)].sz - 1, rc(x), y);
    else
        y = p, split(lc(p), sz, x, lc(y));
    pushup(p);
}

int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (tr[x].k < tr[y].k) {
        pushdown(x);
        rc(x) = merge(rc(x), y);
        pushup(x);return x;
    }
    else {
        pushdown(y);
        lc(y) = merge(x, lc(y));
        pushup(y);return y;
    }
}

void dfs(int x) {
    if (!x) return;
    pushdown(x);
    dfs(lc(x));
    cout << tr[x].v << ' ';
    dfs(rc(x));
}

int n, m;

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= n;++i)
        root = merge(root, initnode(i));

    for (int i = 1;i <= m;++i) {
        int l, r;cin >> l >> r;
        int x, y, z;
        split(root, r, x, z);
        split(x, l - 1, x, y);
        tr[y].lag ^= 1;
        root = merge(merge(x, y), z);
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
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
#define INF (int)(2147483647)
#define MOD (int)(1e8)
#define eps (ld)(1e-9)
#define P (int)(998244353)
#define G (int)(3)
#define mpair(x,y) make_pair(x,y)
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define lc p<<1
#define rc p<<1|1

const int N = 50005;

int n, m;

typedef struct {
    int s[2], p;
    int v, sz;
    void init(int p1, int v1) {
        p = p1, v = v1, sz = 1;
    }
}SplayTree;
SplayTree tr[N * 40];
int root[N << 2], cnt;
int a[N];

void pushup(int x) {
    tr[x].sz = tr[tr[x].s[0]].sz + tr[tr[x].s[1]].sz + 1;
}

void rotate(int x) {
    int y = tr[x].p, z = tr[y].p, k = tr[y].s[1] == x;
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}

void splay(int& root, int x, int k) {
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k) (tr[z].s[0] == y) ^ (tr[y].s[0] == x) ? rotate(x) : rotate(y);
        rotate(x);
    }
    if (!k) root = x;
}

void insert(int& root, int v) {
    int x = root, p = 0;
    while (x) p = x, x = tr[x].s[v > tr[x].v];
    x = ++cnt;
    tr[p].s[v > tr[p].v] = x;
    tr[x].init(p, v);
    splay(root, x, 0);
}

void del(int& root, int v) {
    int x = root;
    while (x) {
        if (tr[x].v == v) break;
        else x = tr[x].s[tr[x].v < v];
    }
    splay(root, x, 0);
    int l = tr[x].s[0], r = tr[x].s[1];
    while (tr[l].s[1]) l = tr[l].s[1];
    while (tr[r].s[0]) r = tr[r].s[0];
    splay(root, l, 0);
    splay(root, r, l);
    tr[r].s[0] = 0;
    splay(root, r, 0);
}

// int find(int root, int v) {
//     int x = root, tar = tr[x].v == v ? x : 0;
//     while (tr[x].s[tr[x].v < v])
//         x = tr[x].s[tr[x].v < v], tar = ((tr[x].v == v) ? x : tar);
//     splay(root, tar, 0);
// }

int getrk(int root, int v) {
    // find(root, v);
    // return tr[tr[root].s[0]].sz;
    int x = root, rk = 0;
    while (x) {
        if (tr[x].v < v) rk += tr[tr[x].s[0]].sz + 1, x = tr[x].s[1];
        else x = tr[x].s[0];
    }
    return rk;
}

int getpre(int root, int v) {
    int x = root, res = -INF;
    while (x) {
        if (tr[x].v < v) res = tr[x].v;
        x = tr[x].s[tr[x].v < v];
    }
    return res;
}

int getsuc(int root, int v) {
    int x = root, res = INF;
    while (x) {
        if (tr[x].v > v) res = tr[x].v;
        x = tr[x].s[tr[x].v <= v];
    }
    return res;
}

void build(int p, int l, int r) {
    insert(root[p], -INF), insert(root[p], INF);
    for (int i = l;i <= r;++i) insert(root[p], a[i]);
    if (l == r) return;
    int m = l + r >> 1;
    build(lc, l, m);
    build(rc, m + 1, r);
}

void update(int p, int l, int r, int pos, int v) {
    del(root[p], a[pos]);
    insert(root[p], v);
    if (l == r) return;
    int m = l + r >> 1;
    if (pos <= m) update(lc, l, m, pos, v);
    else update(rc, m + 1, r, pos, v);
}

int queryrk(int p, int l, int r, int L, int R, int v) {
    if (L <= l && r <= R) return getrk(root[p], v) - 1;
    int m = l + r >> 1, ans = 0;
    if (L <= m) ans += queryrk(lc, l, m, L, R, v);
    if (R > m) ans += queryrk(rc, m + 1, r, L, R, v);
    return ans;
}

int queryv(int L, int R, int rk) {
    int l = 0, r = 1e8, ans;
    while (l <= r) {
        int m = l + r >> 1;
        if (queryrk(1, 1, n, L, R, m) + 1 <= rk) ans = m, l = m + 1;
        else r = m - 1;
    }
    return ans;
}

int querypre(int p, int l, int r, int L, int R, int v) {
    if (L <= l && r <= R) return getpre(root[p], v);
    int m = l + r >> 1, ans = -INF;
    if (L <= m) ans = max(ans, querypre(lc, l, m, L, R, v));
    if (R > m) ans = max(ans, querypre(rc, m + 1, r, L, R, v));
    return ans;
}

int querysuc(int p, int l, int r, int L, int R, int v) {
    if (L <= l && r <= R) return getsuc(root[p], v);
    int m = l + r >> 1, ans = INF;
    if (L <= m) ans = min(ans, querysuc(lc, l, m, L, R, v));
    if (R > m) ans = min(ans, querysuc(rc, m + 1, r, L, R, v));
    return ans;
}

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= n;++i) cin >> a[i];
    build(1, 1, n);

    int occ = 1;

    for (int i = 1;i <= m;++i) {
        int op;cin >> op;
        if (op == 1) {
            int l, r, k;cin >> l >> r >> k;
            cout << queryrk(1, 1, n, l, r, k) + 1 << endl;
        }
        else if (op == 2) {
            int l, r, k;cin >> l >> r >> k;
            cout << queryv(l, r, k) << endl;
        }
        else if (op == 3) {
            int pos, k;cin >> pos >> k;
            update(1, 1, n, pos, k);
            a[pos] = k;
        }
        else if (op == 4) {
            int l, r, k;cin >> l >> r >> k;
            cout << querypre(1, 1, n, l, r, k) << endl;
        }
        else {
            int l, r, k;cin >> l >> r >> k;
            cout << querysuc(1, 1, n, l, r, k) << endl;
        }
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
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

#define lc(x) tr[x].lc
#define rc(x) tr[x].rc

// 线段树套Treap

const int N = 5e4 + 5;

int n, m;

// FHQ Treap 

typedef struct {
    int v, k;
    int lc, rc, p;
    int sz;
}FHQTreap;
FHQTreap tr[N * 40];
rand rnd(clock());
int cnt;

inline int initnode(int v) {
    tr[++cnt].v = v;
    tr[cnt].k = rnd();
    tr[cnt].sz = 1;
    return cnt;
}

inline void pushup(int x) {
    tr[x].sz = tr[lc(x)].sz + tr[rc(x)].sz + 1;
}

inline void split(int p, int v, int& x, int& y) {
    if (!p) { x = y = 0;return; }
    if (tr[p].v <= v)  x = p, split(rc(p), v, rc(x), y);
    else y = p, split(lc(p), v, x, lc(y));
    pushup(p);
}

inline int merge(int x, int y) {
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

inline void insert(int& root, int v) {
    int x, y, z;
    split(root, v, x, y);
    x = merge(x, initnode(v));
    root = merge(x, y);
}

inline void del(int& root, int v) {
    int x, y, z;
    split(root, v, x, y);
    split(x, v - 1, x, z);
    z = merge(lc(z), rc(z));
    root = merge(merge(x, z), y);
}

inline int getid(int p, int rk) {
    if (rk <= tr[lc(p)].sz)
        return getid(lc(p), rk);
    else if (rk > tr[lc(p)].sz + 1)
        return getid(rc(p), rk - tr[lc(p)].sz - 1);
    else return p;
}

inline int getrk(int p, int v) {
    if (!p) return 0;
    if (tr[p].v == v)return getrk(lc(p), v);
    else if (tr[p].v < v)return tr[lc(p)].sz + 1 + getrk(rc(p), v);
    else return getrk(lc(p), v);
}

inline int getpre(int& root, int v) {
    int x, y;
    split(root, v - 1, x, y);
    int ans = tr[getid(x, tr[x].sz)].v;
    root = merge(x, y);
    return ans;
}


inline int getsuc(int& root, int v) {
    int x, y;
    split(root, v, x, y);
    int ans = tr[getid(y, 1)].v;
    root = merge(x, y);
    return ans;
}

// 线段树
#define lc p<<1
#define rc p<<1|1

int a[N];

int root[N << 2];

inline void build(int p, int l, int r) {
    insert(root[p], INF), insert(root[p], -INF);
    for (int i = l;i <= r;++i) insert(root[p], a[i]);
    if (l == r) return;
    int m = l + r >> 1;
    build(lc, l, m);
    build(rc, m + 1, r);
}

inline int queryrk(int p, int l, int r, int L, int R, int k) {
    if (L <= l && r <= R) return getrk(root[p], k) - 1;
    int m = l + r >> 1, ans = 0;
    if (m >= L) ans += queryrk(lc, l, m, L, R, k);
    if (m < R) ans += queryrk(rc, m + 1, r, L, R, k);
    return ans;
}

inline int queryv(int L, int R, int rk) {
    int l = 0, r = 1e8, ans;
    while (l <= r) {
        int m = l + r >> 1;
        if (queryrk(1, 1, n, L, R, m) + 1 <= rk) ans = m, l = m + 1;
        else r = m - 1;
    }
    return ans;
}

inline void update(int p, int l, int r, int pos, int v) {
    del(root[p], a[pos]);
    insert(root[p], v);
    if (l == r) return;
    int m = l + r >> 1;
    if (pos <= m) update(lc, l, m, pos, v);
    else update(rc, m + 1, r, pos, v);
}

inline int querypre(int p, int l, int r, int L, int R, int k) {
    if (L <= l && r <= R) return getpre(root[p], k);
    int m = l + r >> 1, ans = -INF;
    if (L <= m) ans = max(ans, querypre(lc, l, m, L, R, k));
    if (R > m) ans = max(ans, querypre(rc, m + 1, r, L, R, k));
    return ans;
}

inline int querysuc(int p, int l, int r, int L, int R, int k) {
    if (L <= l && r <= R) return getsuc(root[p], k);
    int m = l + r >> 1, ans = INF;
    if (L <= m) ans = min(ans, querysuc(lc, l, m, L, R, k));
    if (R > m) ans = min(ans, querysuc(rc, m + 1, r, L, R, k));
    return ans;
}

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= n;++i) cin >> a[i];
    build(1, 1, n);

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
            int pos, v;cin >> pos >> v;
            update(1, 1, n, pos, v);
            a[pos] = v;
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
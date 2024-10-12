#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define complex complex<ld>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define PI (ld)(3.141592653589793)
#define INF (int)(1e14)
#define MOD (int)(1e9+9)
#define eps (ld)(1e-12)
#define P (int)(998244353)
#define G (int)(3)
// #define lc p<<1
// #define rc p<<1|1
// #define lc(x) tr[x].lc
// #define rc(x) tr[x].rc
#define lc(name,x) name[x].lc
#define rc(name,x) name[x].rc

const int N = 1e5 + 10;
const int M = 2e5 + 10;

int n, m;

typedef struct {
    int lc, rc;
    int val;
}SegTree;
SegTree f[N * 64], sz[N * 64];
int rootf[M], rootsz[M];
int cntf, cntsz;

// build
void buildf(int& x, int l, int r) {
    x = ++cntf;
    if (l == r) { f[x].val = l; return; }
    int m = l + r >> 1;
    buildf(lc(f, x), l, m);
    buildf(rc(f, x), m + 1, r);
}
void buildsz(int& x, int l, int r) {
    x = ++cntsz;
    if (l == r) { sz[x].val = 1; return; }
    int m = l + r >> 1;
    buildsz(lc(sz, x), l, m);
    buildsz(rc(sz, x), m + 1, r);
}

// query
int queryf(int x, int l, int r, int loc) {
    if (l == r) return f[x].val;
    int m = l + r >> 1;
    if (loc <= m) return queryf(lc(f, x), l, m, loc);
    else return queryf(rc(f, x), m + 1, r, loc);
}
int querysz(int x, int l, int r, int loc) {
    if (l == r) return sz[x].val;
    int m = l + r >> 1;
    if (loc <= m) return querysz(lc(sz, x), l, m, loc);
    else return querysz(rc(sz, x), m + 1, r, loc);
}

// find
int find(int x, int a) {
    int fa = queryf(x, 1, n, a);
    if (fa == a) return a;
    else return find(x, fa);
}

// update
void updatef(int x, int& y, int l, int r, int loc, int val) {
    y = ++cntf;
    f[y] = f[x];
    if (l == r) {
        f[y].val = val;
        return;
    }
    int m = l + r >> 1;
    if (loc <= m) updatef(lc(f, x), lc(f, y), l, m, loc, val);
    else updatef(rc(f, x), rc(f, y), m + 1, r, loc, val);
}
void updatesz(int x, int& y, int l, int r, int loc, int val) {
    y = ++cntsz;
    sz[y] = sz[x];
    if (l == r) {
        sz[y].val = val;
        return;
    }
    int m = l + r >> 1;
    if (loc <= m) updatesz(lc(sz, x), lc(sz, y), l, m, loc, val);
    else updatesz(rc(sz, x), rc(sz, y), m + 1, r, loc, val);
}

// combine
void combine(int x, int y, int a, int b) {
    a = find(rootf[x], a);
    b = find(rootf[x], b);
    if (a != b) {
        int sz_a = querysz(rootsz[x], 1, n, a);
        int sz_b = querysz(rootsz[x], 1, n, b);
        if (sz_a < sz_b) swap(a, b);
        updatef(rootf[x], rootf[y], 1, n, b, a);
        updatesz(rootsz[x], rootsz[y], 1, n, a, sz_b + sz_a);
    }
    else {
        rootf[y] = rootf[x];
        rootsz[y] = rootsz[x];
    }
}

void solve() {
    cin >> n >> m;
    buildf(rootf[0], 1, n);
    buildsz(rootsz[0], 1, n);

    for (int i = 1;i <= m;++i) {
        int op;cin >> op;
        if (op == 1) {
            int a, b;cin >> a >> b;
            combine(i - 1, i, a, b);
        }
        else if (op == 2) {
            int k;cin >> k;
            rootf[i] = rootf[k];
            rootsz[i] = rootsz[k];
        }
        else {
            rootf[i] = rootf[i - 1];
            rootsz[i] = rootsz[i - 1];
            int a, b;cin >> a >> b;
            cout << (find(rootf[i], a) == find(rootf[i], b)) << endl;
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
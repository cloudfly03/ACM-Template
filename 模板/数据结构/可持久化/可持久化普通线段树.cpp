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
#define lc p<<1
#define rc p<<1|1
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc

const int N = 1e6 + 1;

int n, m;
int a[N];

typedef struct {
    int lc, rc;
    int val;
}SegTree;
SegTree tr[N * 23];
int root[N];
int cnt;

void build(int& x, int l, int r) {
    x = ++cnt;
    if (l == r) {
        tr[x].val = a[l];
        return;
    }
    int m = l + r >> 1;
    build(lc(x), l, m);
    build(rc(x), m + 1, r);
}

void update(int x, int& y, int l, int r, int loc, int val) {
    y = ++cnt;
    tr[y] = tr[x];
    if (l == r) {
        tr[y].val = val;
        return;
    }
    int m = l + r >> 1;
    if (loc <= m) update(lc(x), lc(y), l, m, loc, val);
    else update(rc(x), rc(y), m + 1, r, loc, val);
}

int query(int x, int l, int r, int loc) {
    if (l == r) return tr[x].val;
    int m = l + r >> 1;
    if (loc <= m) return query(lc(x), l, m, loc);
    else return query(rc(x), m + 1, r, loc);
}

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= n;++i) cin >> a[i];

    build(root[0], 1, n);

    int tot = 0;
    for (int i = 1;i <= m;++i) {
        int ver, t, loc;
        cin >> ver >> t >> loc;
        if (t == 1) {
            int val;cin >> val;
            update(root[ver], root[++tot], 1, n, loc, val);
        }
        else {
            root[++tot] = root[ver];
            cout << query(root[ver], 1, n, loc) << endl;
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
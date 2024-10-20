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

const int N = 2e5 + 5;

int n, m;
int a[N], b[N];

typedef struct {
    int lc, rc;
    int t;
}SegTree;
SegTree tr[N * 22];
int root[N];
int cnt;

void build(int& x, int l, int r) {
    x = ++cnt;
    if (l == r) return;
    int m = l + r >> 1;
    build(lc(x), l, m);
    build(rc(x), m + 1, r);
}

void update(int x, int& y, int l, int r, int val) {
    y = ++cnt;tr[y] = tr[x];tr[y].t++;
    if (l == r) return;
    int m = l + r >> 1;
    if (val <= m) update(lc(x), lc(y), l, m, val);
    else update(rc(x), rc(y), m + 1, r, val);
}

int query(int x, int y, int l, int r, int k) {
    if (l == r) return l;
    int m = l + r >> 1;
    int s = tr[lc(y)].t - tr[lc(x)].t;
    if (k <= s) return query(lc(x), lc(y), l, m, k);
    else return query(rc(x), rc(y), m + 1, r, k - s);
}

void solve() {
    cin >> n >> m;

    for (int i = 1;i <= n;++i) cin >> a[i];
    memcpy(b, a, sizeof a);
    sort(b + 1, b + n + 1);
    int s = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1;i <= n;++i)
        a[i] = lower_bound(b + 1, b + s + 1, a[i]) - b;

    build(root[0], 1, s);

    for (int i = 1;i <= n;++i) update(root[i - 1], root[i], 1, s, a[i]);

    for (int i = 1;i <= m;++i) {
        int l, r, k;cin >> l >> r >> k;
        cout << b[query(root[l - 1], root[r], 1, s, k)] << endl;
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
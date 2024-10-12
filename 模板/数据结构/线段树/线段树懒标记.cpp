#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define endl '\n'
#define MOD 998244353
#define INF 1e14
#define lc (p<<1)
#define rc (p<<1|1)

const int N = 1e5 + 10;

typedef struct {
    int l, r;
    int sum;
    int add;
}SegTree;
SegTree tr[N << 2];

int a[N];
int n, m;

void pushup(int p) {
    tr[p].sum = tr[lc].sum + tr[rc].sum;
}

void pushdown(int p) {
    if (tr[p].add) {
        tr[lc].add += tr[p].add;
        tr[rc].add += tr[p].add;
        tr[lc].sum += (tr[lc].r - tr[lc].l + 1) * tr[p].add;
        tr[rc].sum += (tr[rc].r - tr[rc].l + 1) * tr[p].add;
        tr[p].add = 0;
    }
}

void build(int p, int l, int r) {
    tr[p] = { l,r,a[l] };
    if (l == r) return;
    int m = l + r >> 1;
    build(lc, l, m);
    build(rc, m + 1, r);
    pushup(p);
}

void update(int p, int l, int r, int k) {
    if (tr[p].l >= l && tr[p].r <= r) {
        tr[p].sum += (tr[p].r - tr[p].l + 1) * k;
        tr[p].add += k;
        return;
    }
    int m = tr[p].l + tr[p].r >> 1;

    if (l <= m) update(lc, l, r, k);
    if (r > m) update(rc, l, r, k);
    pushup(p);
}

int query(int p, int l, int r) {
    if (l <= tr[p].l && r >= tr[p].r)
        return tr[p].sum;
    int ans = 0;
    int m = tr[p].l + tr[p].r >> 1;
    pushdown(p);
    pushup(p);
    if (l <= m) ans += query(lc, l, r);
    if (r > m) ans += query(rc, l, r);
    return ans;
}

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= n;++i) cin >> a[i];

    build(1, 1, n);

    for (int i = 1;i <= m;++i) {
        int z, x, y;cin >> z >> x >> y;
        if (z == 1) {
            int val;cin >> val;
            update(1, x, y, val);
        }
        else cout << query(1, x, y) << endl;
    }
}

signed main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);

    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}
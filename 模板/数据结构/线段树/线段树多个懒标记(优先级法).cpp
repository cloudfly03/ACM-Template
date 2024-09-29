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
    int add, mul;//懒标记
}SegTree;
SegTree tr[N << 2];

int a[N];
int n, m, q;

void pushup(int p) {
    tr[p].sum = (tr[lc].sum + tr[rc].sum) % q;
}

void pushdown(int p) {
    if (tr[p].mul != 1) {
        tr[lc].sum = tr[lc].sum * tr[p].mul % q;
        tr[rc].sum = tr[rc].sum * tr[p].mul % q;

        tr[lc].add = tr[lc].add * tr[p].mul % q;
        tr[rc].add = tr[rc].add * tr[p].mul % q;

        tr[lc].mul = tr[lc].mul * tr[p].mul % q;
        tr[rc].mul = tr[rc].mul * tr[p].mul % q;

        tr[p].mul = 1;
    }
    if (tr[p].add) {
        tr[lc].sum = (tr[lc].sum + (tr[lc].r - tr[lc].l + 1) * tr[p].add) % q;
        tr[rc].sum = (tr[rc].sum + (tr[rc].r - tr[rc].l + 1) * tr[p].add) % q;
        tr[lc].add = (tr[lc].add + tr[p].add) % q;
        tr[rc].add = (tr[rc].add + tr[p].add) % q;

        tr[p].add = 0;
    }
}

void build(int p, int l, int r) {
    tr[p] = { l,r,a[l],0,1 };
    if (l == r) return;
    int m = l + r >> 1;
    build(lc, l, m);
    build(rc, m + 1, r);
    pushup(p);
}


void update1(int p, int l, int r, int k) {
    if (l <= tr[p].l && tr[p].r <= r) {
        tr[p].sum = tr[p].sum * k % q;
        tr[p].add = tr[p].add * k % q;
        tr[p].mul = tr[p].mul * k % q;
        return;
    }

    int m = tr[p].l + tr[p].r >> 1;
    pushdown(p);
    if (m >= l) update1(lc, l, r, k);
    if (m < r) update1(rc, l, r, k);
    pushup(p);
}

void update2(int p, int l, int r, int k) {
    if (l <= tr[p].l && tr[p].r <= r) {
        tr[p].sum = (tr[p].sum + (tr[p].r - tr[p].l + 1) * k) % q;
        tr[p].add = (tr[p].add + k) % q;
        return;
    }

    int m = tr[p].l + tr[p].r >> 1;
    pushdown(p);
    if (m >= l) update2(lc, l, r, k);
    if (m < r) update2(rc, l, r, k);
    pushup(p);
}

int query(int p, int l, int r) {
    if (l <= tr[p].l && tr[p].r <= r)
        return tr[p].sum % q;

    int ans = 0;
    int m = tr[p].l + tr[p].r >> 1;
    pushdown(p);
    if (m >= l) ans += query(lc, l, r);
    if (m < r) ans += query(rc, l, r);
    return ans % q;
}

void solve() {
    cin >> n >> m >> q;
    for (int i = 1;i <= n;++i)
        cin >> a[i];

    build(1, 1, n);

    for (int i = 1;i <= m;++i) {
        int z, x, y;cin >> z >> x >> y;
        if (z == 1) {
            int k;cin >> k;
            update1(1, x, y, k);
        }
        else if (z == 2) {
            int k;cin >> k;
            update2(1, x, y, k);
        }
        else
            cout << query(1, x, y) % q << endl;
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
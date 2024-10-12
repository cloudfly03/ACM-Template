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
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
// #define lc(name,x) name[x].lc
// #define rc(name,x) name[x].rc

const int N = 1e5 + 10;
const int M = 2e5 + 10;

int n, m;

typedef struct {
    int lc, rc;
    int f, rk;
}SegTree;
SegTree tr[N * 100];
int root[M];
int cnt;

void build(int& x, int l, int r) {
    x = ++cnt;
    if (l == r) { tr[x].f = l, tr[x].rk = 1; return; }
    int m = l + r >> 1;
    build(lc(x), l, m);
    build(rc(x), m + 1, r);
}

pii query(int x, int l, int r, int loc) {
    if (l == r) return make_pair(tr[x].f, tr[x].rk);
    int m = l + r >> 1;
    if (loc <= m) return query(lc(x), l, m, loc);
    else return query(rc(x), m + 1, r, loc);
}

pii find(int x, int a) {
    auto p = query(x, 1, n, a);
    if (p.first == a) return p;
    else return find(x, p.first);
}

void update(int x, int& y, int l, int r, int loc, int f, int rk) {
    y = ++cnt;
    tr[y] = tr[x];
    if (l == r) {
        tr[y].f = (!f ? tr[y].f : f);
        tr[y].rk = (!rk ? tr[y].rk : rk);
        return;
    }
    int m = l + r >> 1;
    if (loc <= m) update(lc(x), lc(y), l, m, loc, f, rk);
    else update(rc(x), rc(y), m + 1, r, loc, f, rk);
}

void combine(int x, int y, int a, int b) {
    auto [A, rk_a] = find(root[x], a);
    auto [B, rk_b] = find(root[x], b);

    if (A != B) {
        if (rk_a < rk_b) swap(A, B), swap(rk_a, rk_b);
        update(root[x], root[y], 1, n, B, A, 0);
        update(root[y], root[y + 1], 1, n, A, 0, rk_a + 1);
        root[y] = root[y + 1];
    }
    else root[y] = root[x];
}

void solve() {
    cin >> n >> m;
    build(root[0], 1, n);

    for (int i = 1;i <= m;++i) {
        int op;cin >> op;
        if (op == 1) {
            int a, b;cin >> a >> b;
            combine(i - 1, i, a, b);
        }
        else if (op == 2) {
            int k;cin >> k;
            root[i] = root[k];
        }
        else {
            root[i] = root[i - 1];
            int a, b;cin >> a >> b;
            cout << (find(root[i], a).first == find(root[i], b).first) << endl;
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
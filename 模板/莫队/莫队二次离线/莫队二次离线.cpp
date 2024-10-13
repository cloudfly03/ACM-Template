#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define INF 1e14
#define MOD 998244353
#define lc p<<1
#define rc p<<1|1

const int N = 1e5 + 1;
const int M = 1 << 14;

int n, m, k;
int a[N];
int t[M];
vector<int> b;
int pre[N];
int seg;
int ans[N];

typedef struct {
    int l, r;
    int id;
    int ret;
}Query;
Query q[N];

typedef struct {
    int l, r;
    int id;
    int tp;
}F;
vector<F> f[N];

bool cnt(int x) {
    int t = 0;
    while (x) t += x & 1, x >>= 1;
    return t == k;
}

void solve() {
    cin >> n >> m >> k;
    seg = pow(n, 0.5);
    for (int i = 1;i <= n;++i)
        cin >> a[i];
    for (int i = 0;i <= (1 << 14) - 1;++i)
        if (cnt(i)) b.emplace_back(i);
    for (int i = 1;i <= n;++i) {
        pre[i] = t[a[i]];
        for (auto v : b) t[a[i] ^ v]++;
    }
    for (int i = 1;i <= m;++i) {
        cin >> q[i].l >> q[i].r;
        q[i].id = i;
    }

    sort(q + 1, q + m + 1,
        [&](const Query a, const Query b) -> bool {
            if (a.l / seg != b.l / seg) return a.l < b.l;
            return (a.l / seg) & 1 ? a.r > b.r: a.r < b.r;
        }
    );

    for (int i = 1, l = 1, r = 0;i <= m;++i) {
        if (r < q[i].r) f[l - 1].emplace_back((F) { r + 1, q[i].r, i, -1 });
        while (r < q[i].r) q[i].ret += pre[++r];

        if (r > q[i].r) f[l - 1].emplace_back((F) { q[i].r + 1, r, i, 1 });
        while (r > q[i].r) q[i].ret -= pre[r--];

        if (l > q[i].l) f[r].emplace_back((F) { q[i].l, l - 1, i, 1 });
        while (l > q[i].l) q[i].ret -= pre[--l] + !k;

        if (l < q[i].l) f[r].emplace_back((F) { l, q[i].l - 1, i, -1 });
        while (l < q[i].l) q[i].ret += pre[l++] + !k;
    }

    fill(t, t + M, 0);
    for (int i = 1;i <= n;++i) {
        for (auto v : b) t[a[i] ^ v]++;
        for (auto [l, r, id, tp] : f[i])
            while (l <= r) q[id].ret += tp * t[a[l++]];
    }

    for (int i = 2;i <= m;++i) q[i].ret += q[i - 1].ret;
    for (int i = 1;i <= m;++i) ans[q[i].id] = q[i].ret;
    for (int i = 1;i <= m;++i)
        cout << ans[i] << endl;
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
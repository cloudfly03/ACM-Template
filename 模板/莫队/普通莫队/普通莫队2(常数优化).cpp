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

const int N = 5e4 + 1;
int n, m, k;
int a[N];
int seg;
int ans[N];

typedef struct {
    int l, r;
    int id;
}Query;
Query q[N];

bool cmp(Query a, Query b) {
    if (a.l / seg != b.l / seg) return a.l < b.l;
    //s型常数优化
    return (a.l / seg) & 1 ? a.r > b.r: a.r < b.r;
}

int res, cnt[N];

void add(int v) {
    res += 2 * (cnt[v]++) + 1;
}

void del(int v) {
    res += -2 * (cnt[v]--) + 1;
}

void solve() {
    cin >> n >> m >> k;
    seg = pow(n, 0.5);
    for (int i = 1;i <= n;++i)
        cin >> a[i];
    for (int i = 1;i <= m;++i) {
        cin >> q[i].l >> q[i].r;
        q[i].id = i;
    }

    sort(q + 1, q + m + 1, cmp);

    for (int i = 1, l = 1, r = 0;i <= m;++i) {
        while (l > q[i].l) add(a[--l]);
        while (r < q[i].r) add(a[++r]);
        while (l < q[i].l) del(a[l++]);
        while (r > q[i].r) del(a[r--]);
        ans[q[i].id] = res;
    }

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
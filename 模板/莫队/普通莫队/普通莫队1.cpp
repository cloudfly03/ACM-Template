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

const int N = 2e5 + 10;
const int M = 1e6 + 1;
int a[N];
int n, m;
int seg;
int ans[N];

typedef struct {
    int l, r;
    int id;
}Query;
Query q[N];
bool cmp(Query a, Query b) {
    if (a.l / seg != b.l / seg) return a.l < b.l;
    return a.r < b.r;
}

int cnt[M], odd;

void add(int v) {
    (cnt[v] & 1) ? odd-- : odd++;
    ++cnt[v];
}

void del(int v) {
    (cnt[v] & 1) ? odd-- : odd++;
    --cnt[v];
}

void solve() {
    cin >> n >> m;
    seg = pow(n, 0.5);
    for (int i = 1;i <= n;++i)
        cin >> a[i];
    for (int i = 1;i <= m;++i) {
        cin >> q[i].l >> q[i].r;
        q[i].id = i;
    }

    sort(q + 1, q + m + 1, cmp);

    int l = 1, r = 0;
    for (int i = 1;i <= m;++i) {
        if ((q[i].r - q[i].l + 1) & 1) {
            ans[q[i].id] = 1;
            continue;
        }
        while (r < q[i].r) add(a[++r]);
        while (l > q[i].l) add(a[--l]);
        while (r > q[i].r) del(a[r--]);
        while (l < q[i].l) del(a[l++]);
        ans[q[i].id] = odd;
    }

    while (l <= r) del(a[l++]);

    for (int i = 1;i <= m;++i)
        cout << (ans[i] ? "NO" : "YES") << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
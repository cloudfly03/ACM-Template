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

int n, m;
int a[N];
int seg, blocks;

typedef struct {
    int l, r;
    int id;
}Query;
Query q[N];
bool ans[N];
int block(int x) {
    return (x - 1) / seg + 1;
}
bool cmp(Query a, Query b) {
    if (block(a.l) != block(b.l)) return a.l < b.l;
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
    blocks = block(n);
    for (int i = 1;i <= n;++i)
        cin >> a[i];
    for (int i = 1;i <= m;++i) {
        cin >> q[i].l >> q[i].r;
        q[i].id = i;
    }

    sort(q + 1, q + m + 1, cmp);

    int x = 1, l, r;

    for (int i = 1;i <= blocks && x <= m;++i) {
        int B = min(i * seg, n);
        l = B, r = B - 1;
        for (;block(q[x].l) == i && x <= m;++x) {
            if ((q[x].r - q[x].l + 1) & 1) {
                ans[q[x].id] = 1;
                continue;
            }
            while (r < q[x].r) add(a[++r]);
            while (l > q[x].l) add(a[--l]);
            while (r > q[x].r) del(a[r--]);
            while (l < q[x].l) del(a[l++]);
            ans[q[x].id] = odd;
        }
        while (l <= r) del(a[l++]);
    }

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
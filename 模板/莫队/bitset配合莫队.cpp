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

const int N = 1e5 + 10;
const int M = 40000;
int n, m;
int a[N], b[N];
int seg;
int ans[M];

typedef struct {
    int l, r;
    int id;
}Query;
Query q[M * 3];
int cnt;

int p[N];
bitset<N> bs[M], now;

void add(int v) {
    now.set(v + p[v]);
    p[v]++;
}

void del(int v) {
    p[v]--;
    now.reset(v + p[v]);
}

void solve() {
    cin >> n >> m;
    seg = pow(n, 0.5);
    for (int i = 1;i <= n;++i)
        cin >> a[i];
    memcpy(b, a, sizeof a);
    sort(b + 1, b + n + 1);
    for (int i = 1;i <= n;++i)
        a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;

    int z = m / 3 + 1, tot;
    for (int alpha = 1;alpha <= 3 && m;++alpha) {
        m -= tot = min(m, z);
        cnt = 0;
        memset(p, 0, sizeof p);
        now.reset();
        for (int i = 1;i <= tot;++i) {
            bs[i].set();
            ans[i] = 0;
            for (int j = 1;j <= 3;++j) {
                ++cnt;
                cin >> q[cnt].l >> q[cnt].r;
                q[cnt].id = i;
                ans[i] += q[cnt].r - q[cnt].l + 1;
            }
        }

        sort(q + 1, q + cnt + 1,
            [&](Query a, Query b) ->bool {
                if (a.l / seg != b.l / seg) return a.l < b.l;
                return (a.l / seg) & 1 ? a.r > b.r: a.r < b.r;
            }
        );

        for (int i = 1, l = 1, r = 0;i <= cnt;++i) {
            while (l > q[i].l) add(a[--l]);
            while (r < q[i].r) add(a[++r]);
            while (l < q[i].l) del(a[l++]);
            while (r > q[i].r) del(a[r--]);
            bs[q[i].id] &= now;
        }

        for (int i = 1;i <= tot;++i)
            cout << ans[i] - bs[i].count() * 3 << endl;
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
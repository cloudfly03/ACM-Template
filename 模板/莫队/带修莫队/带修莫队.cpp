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

const int N = 133334;
const int M = 1e6 + 1;
int n, m;
int a[N];
int seg;
int ans[N];

typedef struct {
    int l, r;
    int t;
    int id;
}Query;
typedef struct {
    int id, v;
}Update;
Query q[N];
Update u[N];
int cq, cu;
int block(int x) {
    return (x - 1) / seg + 1;
}
bool cmp(Query a, Query b) {
    if (block(a.l) != block(b.l)) return a.l < b.l;
    if (block(a.r) != block(b.r)) return a.r < b.r;
    return a.t < b.t;
}

int cnt[M];
int res = 0;

void add(int v) {
    if (!(cnt[v]++)) res++;
}

void del(int v) {
    if (!(--cnt[v])) res--;
}

void solve() {
    cin >> n >> m;
    seg = pow(n, 0.666);
    for (int i = 1;i <= n;++i)
        cin >> a[i];
    for (int i = 1;i <= m;++i) {
        char tp;cin >> tp;
        int l, r;cin >> l >> r;
        if (tp == 'Q') q[++cq] = { l,r,cu,cq };
        else u[++cu] = { l,r };
    }

    sort(q + 1, q + cq + 1, cmp);

    for (int i = 1, l = 1, r = 0, t = 0;i <= cq;++i) {
        while (l > q[i].l) add(a[--l]);
        while (r < q[i].r) add(a[++r]);
        while (l < q[i].l) del(a[l++]);
        while (r > q[i].r) del(a[r--]);
        while (t < q[i].t) {
            int idx = u[++t].id;
            if (idx >= l && idx <= r) { del(a[idx]);add(u[t].v); }
            swap(a[idx], u[t].v);
        }
        while (t > q[i].t) {
            int idx = u[t].id;
            if (idx >= l && idx <= r) { del(a[idx]);add(u[t].v); }
            swap(a[idx], u[t--].v);
        }
        ans[q[i].id] = res;
    }

    for (int i = 1;i <= cq;++i)
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
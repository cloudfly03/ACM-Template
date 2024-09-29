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

int n, m;
int seg, blocks;
int a[N], b[N];
int ans[N];

typedef struct {
    int l, r;
    int id;
}Query;
Query q[N];
int block(int x) {
    return (x - 1) / seg + 1;
}
bool cmp(Query a, Query b) {
    if (block(a.l) != block(b.l)) return a.l < b.l;
    return a.r < b.r;
}

int res;
int cnt[N];

void recover(int v) {
    --cnt[v];
}

void add(int v) {
    if ((++cnt[v]) * b[v] > res) res = cnt[v] * b[v];
}

int calc(int l, int r) {
    int ret = 0;
    for (int i = l;i <= r;++i)
        ret = max(ret, ++cnt[a[i]] * b[a[i]]);
    for (int i = l;i <= r;++i)
        cnt[a[i]]--;
    return ret;
}

void solve() {
    cin >> n >> m;
    seg = pow(n, 0.5);
    blocks = block(n);
    for (int i = 1;i <= n;++i)
        cin >> a[i];

    //离散化
    memcpy(b, a, sizeof a);
    sort(b + 1, b + n + 1);
    int s = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1;i <= n;++i)
        a[i] = lower_bound(b + 1, b + s + 1, a[i]) - b;

    for (int i = 1;i <= m;++i) {
        cin >> q[i].l >> q[i].r;
        q[i].id = i;
    }

    sort(q + 1, q + m + 1, cmp);

    int x = 1, l = 0, r = 0;
    for (int i = 1;i <= blocks && x <= m;++i) {
        //清空
        res = 0;
        while (l <= r) recover(a[l++]);
        //初始化边界
        int B = min(i * seg, n);
        l = B, r = B - 1;
        for (;block(q[x].l) == i && x <= m;++x) {
            if (block(q[x].r) == i) {
                ans[q[x].id] = calc(q[x].l, q[x].r);
                continue;
            }
            while (r < q[x].r) add(a[++r]);
            int tmp = res;
            while (l > q[x].l) add(a[--l]);
            ans[q[x].id] = res;
            res = tmp;
            while (l <= B) recover(a[l++]);
        }
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
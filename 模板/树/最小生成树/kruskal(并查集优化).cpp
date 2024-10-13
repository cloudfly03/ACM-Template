#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define endl '\n'
#define MOD 998244353
#define INF 1e14
// #define lc (p<<1)
// #define rc (p<<1|1)

const int N = 5001;
const int M = 2e5 + 1;

typedef struct {
    int u, v, w;
}Edge;
Edge e[M];

bool cmp(Edge x, Edge y) {
    return x.w < y.w;
}

int n, m;
int f[N], sz[N];

int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= n;++i) {
        sz[i] = 1;
        f[i] = i;
    }
    for (int i = 1;i <= m;++i)
        cin >> e[i].u >> e[i].v >> e[i].w;

    sort(e + 1, e + m + 1, cmp);
    int cnt = 1;
    int ans = 0;
    for (int i = 1;i <= m;++i) {
        auto [u, v, w] = e[i];
        u = find(u), v = find(v);
        if (u != v) {
            if (sz[u] < sz[v]) swap(u, v);
            f[v] = f[u];
            sz[u] += sz[v];
            ans += w;
            ++cnt;
        }

        if (cnt == n) {
            cout << ans << endl;
            return;
        }
    }
    cout << "orz" << endl;
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
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

const int N = 501;
int n, m;
int la[N], lb[N];//可行顶标
bool va[N], vb[N];//是否在交替路中
int e[N][N];
int match[N];
int d[N];

bool dfs(int u) {
    va[u] = true;
    for (int v = 1;v <= n;++v) {
        if (e[u][v] == -INF) continue;
        if (vb[v]) continue;
        if (la[u] + lb[v] == e[u][v]) {
            vb[v] = true;
            if (!match[v] || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
        else d[v] = min(la[u] + lb[v] - e[u][v], d[v]);
    }
    return false;
}

void solve() {
    cin >> n >> m;

    for (int i = 1;i <= n;++i) {
        la[i] = -INF;
        for (int j = 1;j <= n;++j)
            e[i][j] = -INF;
    }

    for (int i = 1;i <= m;++i) {
        int u, v, w;cin >> u >> v >> w;
        e[u][v] = w;
        la[u] = max(la[u], w);
    }

    for (int i = 1;i <= n;++i) {
        while (true) {
            fill(va + 1, va + n + 1, 0);
            fill(vb + 1, vb + n + 1, 0);
            fill(d + 1, d + n + 1, INF);
            if (dfs(i)) break;
            int delta = INF;
            for (int j = 1;j <= n;++j)
                if (!vb[j]) delta = min(delta, d[j]);
            for (int j = 1;j <= n;++j) {
                if (va[j]) la[j] -= delta;
                if (vb[j]) lb[j] += delta;
            }
        }
    }

    int ans = 0;
    for (int i = 1;i <= n;++i)
        ans += e[match[i]][i];
    cout << ans << endl;

    for (int i = 1;i <= n;++i)
        cout << match[i] << ' ';
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
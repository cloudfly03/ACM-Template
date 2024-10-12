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

const int N = 2e4 + 1;
vector<int> e[N];
int n, m;

int dfn[N], low[N], tot;
int root;
bool cut[N];
int ans;

void tarjan(int u) {
    dfn[u] = low[u] = ++tot;
    int child = 0;
    for (auto v : e[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                ++child;
                if (root != u || child > 1) {
                    if (!cut[u]) ans++;
                    cut[u] = true;
                }
            }
        }
        else
            low[u] = min(low[u], dfn[v]);
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= m;++i) {
        int u, v;cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }

    for (root = 1;root <= n;++root)
        if (!dfn[root]) tarjan(root);

    cout << ans << endl;
    for (int i = 1;i <= n;++i)
        if (cut[i]) cout << i << ' ';
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
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


const int N = 1e4 + 1;

vector<int> e[N];
int n, m;

int dfn[N], low[N], tot;
int stk[N], top;
int scc[N], sz[N], cnt;
bool instk[N];

void tarjan(int u) {
    dfn[u] = low[u] = ++tot;
    stk[++top] = u, instk[u] = true;

    for (auto v : e[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (instk[v])
            low[u] = min(low[u], dfn[v]);
    }

    if (dfn[u] == low[u]) {
        int v;++cnt;
        do {
            v = stk[top--];
            instk[v] = false;
            scc[v] = cnt;
            ++sz[cnt];
        } while (v != u);
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= m;++i) {
        int u, v;cin >> u >> v;
        e[u].emplace_back(v);
    }

    for (int i = 1;i <= n;++i) {
        if (!dfn[i]) tarjan(i);
    }

    int ans = 0;
    for (int i = 1;i <= cnt;++i)
        if (sz[i] > 1) ans++;

    cout << ans << endl;
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
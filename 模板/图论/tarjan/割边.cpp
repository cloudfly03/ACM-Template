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

const int N = 151;
const int M = 5005;

int n, m;
typedef struct {
    int v;
    int nxt;
}edge;
edge e[M << 1];
int h[N];
int cnt = 1;
void add(int u, int v) {
    e[++cnt].v = v;
    e[cnt].nxt = h[u];
    h[u] = cnt;
}

int dfn[N], low[N], tot;
int stk[N], top;
int edcc[N], idx;
bool bri[M << 1];

int deg[N];

void tarjan(int u, int inedg) {
    dfn[u] = low[u] = ++tot;
    stk[++top] = u;
    for (int ed = h[u];ed;ed = e[ed].nxt) {
        auto [v, nxt] = e[ed];
        if (!dfn[v]) {
            tarjan(v, ed);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u])
                bri[ed] = bri[ed ^ 1] = true;
        }
        else if (ed != (inedg ^ 1))
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        int v;++idx;
        do {
            v = stk[top--];
            edcc[v] = idx;
        } while (v != u);
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= m;++i) {
        int u, v;cin >> u >> v;
        add(u, v);
        add(v, u);
    }

    for (int i = 1;i <= n;++i)
        if (!dfn[i]) tarjan(i, 0);

    for (int i = 2;i <= cnt;i += 2) {
        if (!bri[i]) continue;
        deg[edcc[e[i].v]]++;
        deg[edcc[e[i ^ 1].v]]++;
    }

    int sum = 0;
    for (int i = 1;i <= idx;++i)
        if (deg[i] == 1) sum++;
    cout << (sum + 1) / 2 << endl;
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
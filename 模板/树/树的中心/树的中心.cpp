#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define ld long double
#define pii pair<int,int>
#define mpair(x,y) make_pair(x,y)
#define complex complex<ld>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define PI (ld)(3.141592653589793)
#define INF (int)(1e14)
#define MOD (int)(1e8)
#define eps (ld)(1e-9)
#define P (int)(998244353)
#define G (int)(3)
#define lc p<<1
#define rc p<<1|1
// #define lc(x) tr[x].lc
// #define rc(x) tr[x].rc
// #define lc(name,x) name[x].lc
// #define rc(name,x) name[x].rc

const int N = 1e5 + 1;

int n;
vector<pii> e[N];
int d1[N], d2[N];
int up[N];
int ans = INF;
vector<int> vex;

int dfs1(int u, int fa) {
    for (auto [v, w] : e[u]) {
        if (v == fa) continue;
        int d = dfs1(v, u) + w;
        if (d >= d1[u]) d2[u] = d1[u], d1[u] = d;
        else if (d > d2[u]) d2[u] = d;
    }
    return d1[u];
}

void dfs2(int u, int fa) {
    int res = max(up[u], d1[u]);
    if (res == ans) vex.emplace_back(u);
    else if (res < ans) {
        ans = res;
        vex.clear();
        vex.emplace_back(u);
    }
    ans = min(ans, max(up[u], d1[u]));
    for (auto [v, w] : e[u]) {
        if (v == fa) continue;
        if (d1[v] + 1 == d1[u]) up[v] = max(up[u], d2[u]) + w;
        else up[v] = max(up[u], d1[u]) + w;
        dfs2(v, u);
    }
}

void solve() {
    cin >> n;
    for (int i = 1;i < n;++i) {
        int u, v, w;cin >> u >> v >> w;
        e[u].emplace_back(v, w);
        e[v].emplace_back(u, w);
    }

    dfs1(1, 0);
    dfs2(1, 0);

    cout << ans << endl;

    for (auto u : vex)
        cout << u << ' ';
    cout << endl;
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
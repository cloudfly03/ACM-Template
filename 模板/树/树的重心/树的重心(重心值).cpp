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
vector<int> e[N];
int sz[N];
int ans = INF;
vector<int> vex;

void dfs(int u, int fa) {
    sz[u] = 1;
    int mx = 0;
    for (auto v : e[u]) {
        if (v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
        mx = max(mx, sz[v]);
    }
    int res = max(mx, n - sz[u]);
    if (res == ans) vex.emplace_back(u);
    else if (res < ans) {
        ans = res;
        vex.clear();
        vex.emplace_back(u);
    }
}


void solve() {
    cin >> n;
    for (int i = 1;i < n;++i) {
        int u, v;cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }

    dfs(1, 0);

    cout << ans << endl;
    for (auto u : vex)
        cout << u << ' ';
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
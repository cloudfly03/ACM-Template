#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define ld long double
#define pii pair<int,int>
#define complex complex<ld>
#define rand mt19937_64
#define endl '\n'
#define PI (ld)(3.141592653589793)
#define INF (int)(1e7+1)
#define MOD (int)(1e8)
#define eps (ld)(1e-9)
#define P (int)(998244353)
#define G (int)(3)
#define mpair(x,y) make_pair(x,y)
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)

const int N = 1e4 + 1;

int n, m;
int ask[N], ans[N];//询问与结果
vector<pii> e[N];//边
int sz[N], root, mxv, tot;//重心，子树大小
int dis[N];//距离
vector<int> d;//距离列表 -> 根
bool del[N];

// 树上dfs找重心,计算子树
void searchroot(int u, int fa) {
    int mx = 0;
    sz[u] = 1;
    for (auto [v, w] : e[u]) {
        if (v == fa || del[v]) continue;
        searchroot(v, u);
        sz[u] += sz[v];
        mx = max(mx, sz[v]);
    }
    mx = max(mx, tot - sz[u]);
    if (mxv > mx) mxv = mx, root = u;
}

// 统计子树上所有点到根的距离
void getdis(int u, int fa) {
    d.emplace_back(dis[u]);
    for (auto [v, w] : e[u]) {
        if (v == fa || del[v]) continue;
        dis[v] = dis[u] + w;
        getdis(v, u);
    }
}

void calc(int u, int w, int f) {
    d.clear();
    dis[u] = w;
    getdis(u, 0);
    sort(all(d));

    for (int i = 1;i <= m;++i) {
        int l = 0, r = d.size() - 1;
        while (l < r) {
            if (d[l] + d[r] <= ask[i]) {
                if (d[l] + d[r] == ask[i]) ans[i] += f;
                ++l;
            }
            else --r;
        }
    }
}

void divide(int u) {
    calc(u, 0, 1);
    del[u] = true;
    for (auto [v, w] : e[u]) {
        if (del[v]) continue;
        calc(v, w, -1);
        mxv = tot = sz[v];
        searchroot(v, 0);
        divide(root);
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 1;i < n;++i) {
        int u, v, w;cin >> u >> v >> w;
        e[u].emplace_back(v, w);
        e[v].emplace_back(u, w);
    }
    for (int i = 1;i <= m;++i) cin >> ask[i];

    mxv = tot = n;
    searchroot(1, 0);
    divide(root);

    for (int i = 1;i <= m;++i)
        cout << (ans[i] ? "AYE" : "NAY") << endl;
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
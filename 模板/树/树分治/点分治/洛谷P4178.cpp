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

const int N = 4e4 + 1;

int n, k;
int ans;// 结果
vector<pii> e[N];// 边
int sz[N], root, mxv, tot;// 重心，子树大小
int dis[N];// 距离
unordered_map<int, int> d;// 距离列表 -> 根
bool del[N];
map<int, int> mp;

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
    d[dis[u]]++;
    for (auto [v, w] : e[u]) {
        if (v == fa || del[v]) continue;
        dis[v] = dis[u] + w;
        getdis(v, u);
    }
}

void calc(int u) {
    mp[0] = 1;

    for (auto [v, w] : e[u]) {
        if (del[v]) continue;
        d.clear();
        dis[v] = w;
        getdis(v, u);

        map<int, int> sum;
        int total = 0;
        for (auto [distance, times] : mp) {
            total += times;
            sum[distance] = total;
        }

        for (auto [distance, times] : d) {
            auto iter = sum.upper_bound(k - distance);
            if (iter == sum.begin()) continue;
            --iter;
            ans += times * (*iter).second;
        }

        for (auto [distance, times] : d)
            if (distance <= k) mp[distance] += times;
    }
    mp.clear();
}

void divide(int u) {
    calc(u);
    del[u] = true;
    for (auto [v, w] : e[u]) {
        if (del[v]) continue;
        mxv = tot = sz[v];
        searchroot(v, 0);
        divide(root);
    }
}

void solve() {
    cin >> n;
    for (int i = 1;i < n;++i) {
        int u, v, w;cin >> u >> v >> w;
        e[u].emplace_back(v, w);
        e[v].emplace_back(u, w);
    }
    cin >> k;

    mxv = tot = n;
    searchroot(1, 0);
    divide(root);

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
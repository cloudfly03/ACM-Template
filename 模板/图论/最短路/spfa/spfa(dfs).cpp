#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define complex complex<ld>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define PI (ld)(3.141592653589793)
#define INF (int)(1e14)
#define MOD (int)(1e9+9)
#define eps (ld)(1e-12)
#define P (int)(998244353)
#define G (int)(3)
#define lc p<<1
#define rc p<<1|1

const int N = 1e5 + 1;
int n, m, s;
vector<pii> e[N];
int dis[N];
bool vis[N];

// true 存在负环 只能判断从1个起点开始的负环
bool spfa(int u) {
    vis[u] = true;

    for (auto [v, w] : e[u])
        if (dis[v] > dis[u] + w) {
            dis[v] = dis[u] + w;
            if (vis[v] || spfa(v)) return true;
        }

    vis[u] = false;
    return false;
}

void solve() {
    cin >> n >> m >> s;
    for (int i = 1;i <= m;++i) {
        int u, v, w;cin >> u >> v >> w;
        e[u].emplace_back(v, w);
    }

    fill(dis + 1, dis + n + 1, INF);
    dis[s] = 0;

    spfa(s);

    for (int i = 1;i <= n;++i)
        cout << dis[i] << ' ';
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
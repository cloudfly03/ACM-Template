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
int e[N][N];
bool vis[N];//右部点是否已访问
int match[N];//记录右部点的匹配点
int pre[N];//记录右部前驱点
int slack[N];//左右顶标与边权最小差

void bfs(int k) {
    fill(slack + 1, slack + n + 1, INF);
    fill(pre + 1, pre + n + 1, 0);
    int d, u, lst = 0, tar;
    match[lst] = k;

    do {
        u = match[lst], vis[lst] = true, d = INF;
        for (int v = 1;v <= n;++v) {
            if (vis[v]) continue;
            if (la[u] + lb[v] - e[u][v] < slack[v])
                slack[v] = la[u] + lb[v] - e[u][v], pre[v] = lst;
            if (slack[v] < d)
                d = slack[v], tar = v;
        }
        for (int v = 0;v <= n;++v) {
            if (vis[v]) la[match[v]] -= d, lb[v] += d;
            else slack[v] -= d;
        }
        lst = tar;
    } while (match[lst]);
    while (lst) match[lst] = match[pre[lst]], lst = pre[lst];
}

void solve() {
    cin >> n >> m;

    for (int i = 1;i <= n;++i)
        for (int j = 1;j <= n;++j)
            e[i][j] = -INF;

    for (int i = 1;i <= m;++i) {
        int u, v, w;cin >> u >> v >> w;
        e[u][v] = w;
    }

    for (int i = 1;i <= n;++i) {
        fill(vis, vis + n + 1, false);
        bfs(i);
    }

    int ans = 0;
    for (int i = 1;i <= n;++i)
        ans += e[match[i]][i];
    cout << ans << endl;

    for (int i = 1;i <= n;++i)
        cout << match[i] << ' ';
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
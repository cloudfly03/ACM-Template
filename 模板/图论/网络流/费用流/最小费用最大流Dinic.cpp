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

const int N = 5e3 + 1;
const int M = 5e4 + 1;

int n, m, S, T;

typedef struct {
    int to, c, f, nxt;
}edge;
edge e[M << 1];
int h[N];
int cnt = 1;
void add(int u, int v, int c, int f) {
    e[++cnt].to = v;
    e[cnt].c = c;
    e[cnt].f = f;
    e[cnt].nxt = h[u];
    h[u] = cnt;
}

int ans_flow, ans_fee;

bool inque[N];
int dis[N];
int ex[N];

bool ISAP() {
    fill(dis + 1, dis + n + 1, INF);
    fill(inque + 1, inque + n + 1, false);
    queue<int> q;
    q.push(S);
    dis[S] = 0;
    inque[S] = true;
    while (q.size()) {
        int u = q.front();q.pop();
        inque[u] = false;
        for (int ed = h[u];ed;ed = e[ed].nxt) {
            auto [v, c, fee, nxt] = e[ed];
            if (dis[v] > dis[u] + fee && c) {
                dis[v] = dis[u] + fee;
                if (!inque[v]) {
                    q.push(v);
                    inque[v] = true;
                }
            }
        }
    }
    return dis[T] != INF;
}

int cur[N];
bool vis[N];

int dfs(int u, int flow) {
    if (u == T) return flow;
    int sum = 0;
    //防止负环
    vis[u] = true;
    for (int ed = cur[u];ed;ed = e[ed].nxt) {
        cur[u] = ed;
        auto [v, c, fee, nxt] = e[ed];
        if (dis[u] + fee == dis[v] && c && !vis[v]) {
            int f = dfs(v, min(flow, c));
            flow -= f;
            sum += f;
            e[ed].c -= f;
            e[ed ^ 1].c += f;
            ans_fee += f * e[ed].f;
            if (!flow) break;
        }
    }
    vis[u] = false;
    if (!sum) vis[u] = true;
    return sum;
}

void Dinic() {
    while (ISAP()) {
        memcpy(cur, h, sizeof h);
        fill(vis + 1, vis + n + 1, false);
        ans_flow += dfs(S, INF);
    }
    cout << ans_flow << ' ' << ans_fee << endl;
}

void solve() {
    cin >> n >> m >> S >> T;
    for (int i = 1;i <= m;++i) {
        int u, v, c, f;
        cin >> u >> v >> c >> f;
        add(u, v, c, f);
        add(v, u, 0, -f);
    }

    Dinic();
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
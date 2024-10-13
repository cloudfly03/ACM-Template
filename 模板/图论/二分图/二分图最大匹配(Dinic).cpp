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

const int N = 1003;
const int M = 2e5;

typedef struct {
    int to, c, nxt;
}edge;
edge e[M];
int h[N];
int cnt = 1;
void add(int u, int v, int c) {
    e[++cnt].to = v;
    e[cnt].c = c;
    e[cnt].nxt = h[u];
    h[u] = cnt;
}

int n, m, x;
int S, T;

int cur[N];
int d[N];

bool bfs() {
    fill(d + 1, d + T + 1, 0);
    queue<int> q;
    q.push(S);
    d[S] = 1;
    while (q.size()) {
        int u = q.front();q.pop();
        for (int ed = h[u];ed;ed = e[ed].nxt) {
            auto [v, c, nxt] = e[ed];
            if (c && !d[v]) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    return d[T];
}

int dfs(int u, int mxflow) {
    if (u == T) return mxflow;
    int sum = 0;
    for (int ed = cur[u];ed;ed = e[ed].nxt) {
        cur[u] = ed;
        auto [v, c, nxt] = e[ed];
        if (d[v] == d[u] + 1 && c) {
            int f = dfs(v, min(mxflow, c));
            e[ed].c -= f;
            e[ed ^ 1].c += f;
            sum += f;
            mxflow -= f;
            if (!mxflow) break;
        }
    }
    if (!sum) d[u] = 0;
    return sum;
}


int Dinic() {
    int flow = 0;
    while (bfs()) {
        memcpy(cur, h, sizeof h);
        flow += dfs(S, INF);
    }
    return flow;
}

void solve() {
    cin >> n >> m >> x;
    S = 0, T = n + m + 1;
    for (int i = 1;i <= x;++i) {
        int u, v;cin >> u >> v;
        add(u, v + n, 1);
        add(v + n, u, 0);
    }
    for (int i = 1;i <= n;++i) {
        add(S, i, 1);
        add(i, S, 0);
    }
    for (int i = 1;i <= m;++i) {
        add(n + i, T, 1);
        add(T, n + i, 0);
    }

    cout << Dinic() << endl;
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
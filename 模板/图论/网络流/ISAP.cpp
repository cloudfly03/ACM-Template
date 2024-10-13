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

const int N = 1201;
const int M = 1.2e5 + 5;
typedef struct {
    int to;
    int c;
    int nxt;
}edge;
edge e[M << 1];
int h[N];
int cnt = 1;
void add(int u, int v, int c) {
    e[++cnt].to = v;
    e[cnt].c = c;
    e[cnt].nxt = h[u];
    h[u] = cnt;
}

int n, m, S, T;
int d[N], num[N], cur[N];

void bfs() {
    fill(num + 1, num + n + 1, 0);
    fill(d + 1, d + n + 1, -1);
    queue<int> q;
    q.push(T);
    d[T] = 0;
    num[0] = 1;

    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int ed = h[u];ed;ed = e[ed].nxt) {
            auto [v, c, nxt] = e[ed];
            if (d[v] == -1 && !c) {
                d[v] = d[u] + 1;
                num[d[v]]++;
                q.push(v);
            }
        }
    }
}

int dfs(int u, int mf) {
    if (u == T) return mf;
    int sum = 0;
    for (int ed = cur[u];ed;ed = e[ed].nxt) {
        cur[u] = ed;//当前弧优化
        auto [v, c, nxt] = e[ed];
        if (d[u] == d[v] + 1 && c) {
            int f = dfs(v, min(mf, c));
            mf -= f;
            sum += f;
            e[ed].c -= f;
            e[ed ^ 1].c += f;
            if (!mf) return sum;//残量优化
        }
    }
    //断层优化
    if (--num[d[u]] == 0) d[S] = n + 1;
    ++d[u];
    ++num[d[u]];
    return sum;
}

int ISAP() {
    bfs();
    int flow = 0;
    while (d[S] < n) {
        memcpy(cur, h, sizeof h);
        flow += dfs(S, INF);
    }
    return flow;
}

void solve() {
    cin >> n >> m >> S >> T;
    for (int i = 1;i <= m;++i) {
        int u, v, c;cin >> u >> v >> c;
        add(u, v, c);
        add(v, u, 0);
    }

    cout << ISAP() << endl;
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
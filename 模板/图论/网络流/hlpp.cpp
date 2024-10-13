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

const int N = 1.2e3 + 1;
const int M = 1.2e5 + 1;

int n, m, S, T;

typedef struct {
    int to, c, nxt;
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

//标号
int H[N], nums[N];
//标号扩展
bool bfs() {
    fill(H + 1, H + n + 1, n);
    queue<int> q;
    H[T] = 0;
    q.push(T);
    while (q.size()) {
        int u = q.front();q.pop();
        for (int ed = h[u];ed;ed = e[ed].nxt) {
            auto [v, c, nxt] = e[ed];
            if (!c && H[v] == n) {
                H[v] = H[u] + 1;
                q.push(v);
            }
        }
    }
    return H[S] != n;
}

// 按标号H从大到小排序
class cmp {
public:
    bool operator()(int a, int b) {
        return H[a] < H[b];
    }
};
priority_queue<int, vector<int>, cmp> q;
bool inque[N];
int mxflow[N];

void relabel(int u) {
    --nums[H[u]];
    //当前层空，上层转移至非法
    if (!nums[H[u]])
        for (int v = 1;v <= n;++v)
            if (H[v] > H[u] && H[v] < n && v != S && v != T) {
                --nums[H[v]];
                H[v] = n;
            }
    H[u] = INF;
    for (int ed = h[u];ed;ed = e[ed].nxt) {
        auto [v, c, nxt] = e[ed];
        if (c && H[u] > H[v] + 1)
            H[u] = H[v] + 1;
    }
    if (H[u] == INF) H[u] = n;
    ++nums[H[u]];
}

int HLPP() {
    if (!bfs()) return 0;
    //层处理
    H[S] = n - 1;
    for (int i = 1;i <= n;++i) ++nums[H[i]];

    //预处理源点直接可达点
    for (int ed = h[S];ed;ed = e[ed].nxt) {
        auto [v, c, nxt] = e[ed];
        if (c) {
            e[ed].c -= c;
            e[ed ^ 1].c += c;
            mxflow[v] += c;
            if (v != S && v != T && !inque[v]) {
                q.push(v);
                inque[v] = true;
            }
        }
    }

    //预流推进
    while (q.size()) {
        int u = q.top();q.pop();
        inque[u] = false;
        for (int ed = h[u];ed;ed = e[ed].nxt) {
            auto [v, c, nxt] = e[ed];
            if (H[v] + 1 == H[u] && c) {
                int f = min(mxflow[u], c);
                mxflow[u] -= f;
                mxflow[v] += f;
                e[ed].c -= f;
                e[ed ^ 1].c += f;
                if (v != S && v != T && !inque[v]) {
                    q.push(v);
                    inque[v] = true;
                }
                if (!mxflow[u]) break;
            }
        }
        if (mxflow[u]) {
            relabel(u);
            if (H[u] == n) continue;
            q.push(u);
            inque[u] = true;
        }
    }

    return mxflow[T];
}

void solve() {
    cin >> n >> m >> S >> T;
    for (int i = 1;i <= m;++i) {
        int u, v, c;
        cin >> u >> v >> c;
        add(u, v, c);
        add(v, u, 0);
    }

    cout << HLPP() << endl;
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
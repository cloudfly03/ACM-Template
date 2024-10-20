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

#define lc(x) tr[x].lc
#define rc(x) tr[x].rc

const int N = 1e5 + 1;

int n, m;
int a[N];
vector<int> e[N];

struct LCA {
    int sz[N], dep[N], fa[N], son[N], top[N];

    void init() {
        dfs1(1, 0);
        dfs2(1, 1);
    }

    void dfs1(int u, int father) {
        fa[u] = father;
        dep[u] = dep[father] + 1;
        sz[u] = 1;
        for (auto v : e[u]) {
            if (v == father) continue;
            dfs1(v, u);
            sz[u] += sz[v];
            if (sz[son[u]] < sz[v]) son[u] = v;
        }
    }

    void dfs2(int u, int t) {
        top[u] = t;
        if (son[u]) dfs2(son[u], t);
        for (auto v : e[u]) {
            if (v == fa[u] || v == son[u]) continue;
            dfs2(v, v);
        }
    }

    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }

    int getdis(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
}lca;

struct SegTree {
    struct Node {
        int lc, rc;
        int sum;
    }tr[N * 40];
    int root[N], cnt;

    void pushup(int p) {
        tr[p].sum = tr[lc(p)].sum + tr[rc(p)].sum;
    }

    void update(int& p, int l, int r, int idx, int v) {
        if (!p) p = ++cnt;
        if (l == r) { tr[p].sum += v;return; }
        int m = l + r >> 1;
        if (idx <= m) update(lc(p), l, m, idx, v);
        else update(rc(p), m + 1, r, idx, v);
        pushup(p);
    }

    int query(int p, int l, int r, int L, int R) {
        if (!p) return 0;
        if (L <= l && r <= R) return tr[p].sum;
        int m = l + r >> 1, ans = 0;
        if (L <= m) ans += query(lc(p), l, m, L, R);
        if (R > m) ans += query(rc(p), m + 1, r, L, R);
        return ans;
    }
}sg, ch;

struct PointTree {
    int sz[N], mxv, tot, root;
    int fa[N], dep[N];
    int dis[N][20];
    bool del[N];

    void findwc(int u, int fa) {
        int mx = 0;
        sz[u] = 1;
        for (auto v : e[u]) {
            if (v == fa || del[v]) continue;
            findwc(v, u);
            sz[u] += sz[v];
            mx = max(mx, sz[v]);
        }
        mx = max(mx, tot - sz[u]);
        if (mx < mxv) mxv = mx, root = u;
    }

    void getroot(int u, int size) {
        root = 0, mxv = tot = size;
        findwc(u, 0);
        findwc(root, 0);//修正sz
    }

    void build(int u) {
        del[u] = true;
        build_sg(u, 0, u, 0);
        for (auto v : e[u]) {
            if (del[v]) continue;
            getroot(v, sz[v]);
            build_ch(v, 0, root, 1);
            fa[root] = u;
            dep[root] = dep[u] + 1;
            build(root);
        }
    }

    void build_sg(int u, int fa, int src, int d) {
        sg.update(sg.root[src], 0, n, d, a[u]);
        for (auto v : e[u]) {
            if (v == fa || del[v]) continue;
            build_sg(v, u, src, d + 1);
        }
    }

    void build_ch(int u, int fa, int src, int d) {
        ch.update(ch.root[src], 0, n, d, a[u]);
        for (auto v : e[u]) {
            if (v == fa || del[v]) continue;
            build_ch(v, u, src, d + 1);
        }
    }

    void init() {
        getroot(1, n);
        build(root);
        lca.init();
        for (int i = 1;i <= n;++i)
            for (int j = i;j;j = fa[j])
                dis[i][dep[i] - dep[j]] = lca.getdis(i, j);
    }

    int query(int u, int k) {
        int ans = sg.query(sg.root[u], 0, n, 0, k);
        for (int v = u;fa[v];v = fa[v]) {
            int d = dis[u][dep[u] - dep[fa[v]]];
            ans += sg.query(sg.root[fa[v]], 0, n, 0, k - d);
            ans -= ch.query(ch.root[v], 0, n, 0, k - d);
        }
        return ans;
    }

    void update(int u, int val) {
        sg.update(sg.root[u], 0, n, 0, val - a[u]);
        for (int v = u;fa[v];v = fa[v]) {
            int d = dis[u][dep[u] - dep[fa[v]]];
            sg.update(sg.root[fa[v]], 0, n, d, val - a[u]);
            ch.update(ch.root[v], 0, n, d, val - a[u]);
        }
    }
}pt;

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= n;++i) cin >> a[i];
    for (int i = 1;i < n;++i) {
        int u, v;cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }

    pt.init();
    int last = 0;
    for (int i = 1;i <= m;++i) {
        int op, x, y;
        cin >> op >> x >> y;
        x ^= last, y ^= last;
        if (op == 0) cout << (last = pt.query(x, y)) << endl;
        else pt.update(x, y), a[x] = y;
    }
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
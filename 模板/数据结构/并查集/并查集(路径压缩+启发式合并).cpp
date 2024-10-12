#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define endl '\n'
#define MOD 998244353
#define INF 1e14

const int N = 1e4 + 1;
int f[N], sz[N], n;
int m;

//路径压缩优化
int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}

void combine(int x, int y) {
    x = find(x), y = find(y);
    if (x != y) {
        //启发式合并
        if (sz[x] < sz[y]) swap(x, y);
        f[y] = x;
        sz[x] += sz[y];
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= n;++i) {
        f[i] = i;
        sz[i] = 1;
    }

    for (int i = 1;i <= m;++i) {
        int z, x, y;
        cin >> z >> x >> y;
        if (z == 1) combine(x, y);
        else cout << (find(x) == find(y) ? "Y" : "N") << endl;
    }
}

signed main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);

    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}
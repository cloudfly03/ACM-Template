#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define endl ('\n')
const int INF = 1e14;
const int MOD = 1e9 + 7;

const int N = 1001;
int n, m;
int f[N], g[N];

void solve() {
    cin >> n >> m;
    fill(g, g + m + 1, 1);
    for (int i = 1;i <= n;++i) {
        int v, w;
        cin >> v >> w;
        for (int j = m;j >= v;--j) {
            if (f[j] < f[j - v] + w) {
                f[j] = f[j - v] + w;
                g[j] = g[j - v];
            }
            else if (f[j] == f[j - v] + w)
                g[j] = (g[j] + g[j - v]) % MOD;
        }
    }
    cout << g[m] << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define endl ('\n')
const int INF = 1e14;
const int MOD = 1e9 + 7;

const int V = 101;
int f[V];

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1;i <= n;++i) {
        int t;cin >> t;
        vector<pii> x;
        while (t--) {
            int v, w;
            cin >> v >> w;
            x.emplace_back(v, w);
        }
        for (int j = m;j;--j) {
            for (auto [v, w] : x) {
                if (j < v) continue;
                f[j] = max(f[j], f[j - v] + w);
            }
        }
    }
    cout << f[m] << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define endl ('\n')
const int INF = 1e14;
const int MOD = 1e9 + 7;


const int N = 1001;
const int V = 1001;

int n, m;
int f[2][V];
int q[N];

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= n;++i) {
        int v, w, s;
        cin >> v >> w >> s;
        if (s == -1) {
            //01背包
            for (int j = m;j >= v;--j)
                f[i & 1][j] = max(f[!(i & 1)][j], f[!(i & 1)][j - v] + w);
        }
        else if (s == 0) {
            //完全背包
            for (int j = v;j <= m;++j)
                for (int k = 1;j - k * v >= 0;++k)
                    f[i & 1][j] = max(f[!(i & 1)][j], f[!(i & 1)][j - k * v] + k * w);
        }
        else {
            //多重背包
            for (int j = 0;j < v;++j) {
                int h = 1, t = 0;
                for (int k = j;k <= m;k += v) {
                    if (h <= t && k - q[h] > s * v) ++h;
                    if (h <= t) f[i & 1][k] = max(f[!(i & 1)][k], f[!(i & 1)][q[h]] + (k - q[h]) / v * w);
                    while (h <= t && f[!(i & 1)][k] - f[!(i & 1)][q[t]] >= (k - q[t]) / v * w) --t;
                    q[++t] = k;
                }
            }
        }
    }
    cout << f[n & 1][m] << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}
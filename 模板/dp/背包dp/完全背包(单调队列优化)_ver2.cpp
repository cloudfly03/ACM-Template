#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define endl ('\n')
const int INF = 1e14;
const int MOD = 1e9 + 7;

const int N = 2e4 + 1;

int n, m;
int f[2][N];
int q[N];

//使用数组模拟单调队列 常数小

void solve() {
    cin >> n >> m;

    for (int i = 1;i <= n;++i) {
        int v, w, s;cin >> v >> w >> s;
        for (int j = 0;j < v;++j) {
            int h = 1, t = 0;
            for (int k = j;k <= m;k += v) {
                if (h <= t && k - q[h] > v * s) ++h;
                if (h <= t) f[i & 1][k] = max(f[!(i & 1)][k], f[!(i & 1)][q[h]] + (k - q[h]) / v * w);
                while (h <= t && ((k - q[t]) / v * w <= f[!(i & 1)][k] - f[!(i & 1)][q[t]])) --t;
                q[++t] = k;
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
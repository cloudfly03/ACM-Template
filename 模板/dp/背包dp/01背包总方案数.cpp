#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define endl ('\n')
const int INF = 1e14;
const int MOD = 1e9 + 7;

const int M = 1001;

int n, m;
int f[M];

void solve() {
    cin >> n >> m;
    fill(f, f + m + 1, 1);
    for (int i = 1;i <= n;++i) {
        int v, w;
        cin >> v >> w;
        for (int j = m;j >= v;--j)
            f[j] = (f[j] + f[j - v]) % MOD;
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
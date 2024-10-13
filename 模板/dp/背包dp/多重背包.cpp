#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define endl ('\n')
const int INF = 1e14;
const int MOD = 1e9 + 7;

const int N = 101;
const int V = 101;

int n, m;
int f[V];
int v[N], w[N], s[N];

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= n;++i)
        cin >> v[i] >> w[i] >> s[i];

    for (int i = 1;i <= n;++i)
        for (int k = 1;k <= s[i];++k) //跑s[i]次01背包
            for (int j = m;j >= v[i];--j)
                f[j] = max(f[j], f[j - v[i]] + w[i]);

    cout << f[m] << endl;
}

signed main() {
    //cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define INF (int)(1e14)
#define MOD (int)(1e9+7)
#define eps (ld)(1e-6)
#define lc p<<1
#define rc p<<1|1

//P1450

const int N = 1e5 + 10;
int c[5], d[5], n, s;
int f[N];

void solve() {
    for (int i = 1;i <= 4;++i) cin >> c[i];
    cin >> n;

    f[0] = 1;
    for (int i = 1;i <= 4;++i)
        for (int j = c[i];j < N;++j)
            f[j] += f[j - c[i]];

    for (int i = 1;i <= n;++i) {
        for (int j = 1;j <= 4;++j) cin >> d[j];
        cin >> s;
        int ans = f[s];
        for (int j = 1;j < (1 << 4);++j) {
            int sign = -1, delta = 0;
            for (int k = 1;k <= 4;++k)
                if (j & 1 << (k - 1)) {
                    delta += c[k] * (d[k] + 1);
                    sign *= -1;
                    if (delta > s) break;
                }
            if (delta <= s) ans -= sign * f[s - delta];
        }
        cout << ans << endl;
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
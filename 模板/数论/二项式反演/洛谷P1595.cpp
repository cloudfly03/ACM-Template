#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define complex complex<ld>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define PI (ld)(3.141592653589793)
#define INF (int)(1e14)
#define MOD (int)(998244353)
#define eps (ld)(1e-12)
#define G (int)(3)
#define lc p<<1
#define rc p<<1|1

const int N = 21;
int g[N];
int n;

void solve() {
    cin >> n;
    g[0] = 1;
    for (int i = 1;i <= n;++i) g[i] = i * g[i - 1];
    int ans = 0;
    int flag = n & 1 ? -1 : 1;
    for (int i = 0;i <= n;++i) {
        ans += flag * g[n] / g[n - i];
        flag *= -1;
    }
    cout << ans << endl;
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
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define INF 1e14
#define MOD 998244353
#define lc p<<1
#define rc p<<1|1

// ax + by = gcd(a,b) 存在整数解

int gcd(int a, int b) {
    return !b ? a : gcd(b, a % b);
}

int n;
void solve() {
    cin >> n;
    int ans = 0;
    for (int i = 1;i <= n;++i) {
        int t;cin >> t;
        ans = gcd(abs(t), ans);
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
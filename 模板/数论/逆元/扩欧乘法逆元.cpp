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

int exgcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    int ret = exgcd(b, a % b, x, y);
    int t = x;
    x = y;
    y = t - a / b * y;
    return ret;
}

int inv(int a, int mod) {
    int l, r;
    exgcd(a, mod, l, r);
    return (l % mod + mod) % mod;
}

int a;

void solve() {
    cin >> a;
    cout << inv(a, MOD) << endl;
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
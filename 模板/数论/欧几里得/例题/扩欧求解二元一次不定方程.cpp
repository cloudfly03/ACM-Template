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
    int ans = exgcd(b, a % b, x, y);
    int t = x;
    x = y;
    y = t - a / b * y;
    return ans;
}

int n;
void solve() {
    cin >> n;
    for (int i = 1;i <= n;++i) {
        int a, b, c;cin >> a >> b >> c;
        int x, y;
        int GCD = exgcd(a, b, x, y);
        if (c % GCD != 0) {
            cout << -1 << endl;
            continue;
        }
        c /= GCD;
        x *= c;
        y *= c;

        int tmin = floor(-1.0 * x * GCD / b) + 1;
        int tmax = ceil(1.0 * y * GCD / a) - 1;
        if (tmin > tmax) {
            x = x + b / GCD * tmin;
            y = y - a / GCD * tmax;
            cout << x << ' ' << y << endl;
        }
        else {
            int xmin, xmax, ymin, ymax;
            xmin = x + b / GCD * tmin;
            xmax = x + b / GCD * tmax;
            ymin = y - a / GCD * tmax;
            ymax = y - a / GCD * tmin;
            cout << tmax - tmin + 1 << ' ' << xmin << ' ' << ymin << ' ' << xmax << ' ' << ymax << endl;
        }
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
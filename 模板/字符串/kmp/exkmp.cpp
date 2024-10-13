#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define endl ('\n')
const int INF = 1e14;
const int MOD = 1e9 + 7;

const int N = 3e7;
string a, b;
int za[N], zb[N];
int ans = 0;

void solve() {
    cin >> b >> a;
    int n = a.size();
    int m = b.size();
    a = ' ' + a;
    b = ' ' + b;
    za[1] = n;
    for (int i = 2, l, r = 0;i <= n;++i) {
        if (i <= r) za[i] = min(za[i - l + 1], r - i + 1);
        while (i + za[i] <= n && a[1 + za[i]] == a[i + za[i]]) za[i]++;
        if (i + za[i] - 1 > r) l = i, r = za[i] + i - 1;
    }

    for (int i = 1;i <= n;++i) {
        ans ^= i * (za[i] + 1);
    }
    cout << ans << endl;
    ans = 0;
    for (int i = 1, l, r = 0;i <= m;++i) {
        if (i <= r) zb[i] = min(za[i - l + 1], r - i + 1);
        while (i + zb[i] <= m && a[1 + zb[i]] == b[i + zb[i]]) zb[i]++;
        if (i + zb[i] - 1 > r) l = i, r = zb[i] + i - 1;
    }
    for (int i = 1;i <= m;++i) {
        ans ^= i * (zb[i] + 1);
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
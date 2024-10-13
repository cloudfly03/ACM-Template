#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define endl ('\n')
const int INF = 1e14;
const int MOD = 1e9 + 7;

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

void solve() {
    int a, b, x, y;
    cin >> a >> b;
    cout << exgcd(a, b, x, y) << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}
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

//给你 n 和 m 个质数
//计算 1 ~ n 中有多少个数至少可以被提供的一个质数整除

const int N = 20;
int n, m;
int a[N];

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= m;++i)
        cin >> a[i];
    int ans = 0;
    for (int i = 1;i < (1 << m);++i) {
        int sign = -1, t = 1;
        for (int j = 0;j < m;++j) {
            if (i >> j & 1) {
                sign *= -1;
                t *= a[j + 1];
            }
            if (t > n) break;
        }
        ans += n / t * sign;
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
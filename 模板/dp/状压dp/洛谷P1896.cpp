#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define mpair(x,y) make_pair(x,y)
#define complex complex<ld>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define PI (ld)(3.141592653589793)
#define INF (int)(1e14)
#define MOD (int)(1e9)
#define eps (ld)(1e-9)
#define P (int)(998244353)
#define G (int)(3)
// #define lc p<<1
// #define rc p<<1|1
// #define lc(x) tr[x].lc
// #define rc(x) tr[x].rc
// #define lc(name,x) name[x].lc
// #define rc(name,x) name[x].rc

const int N = 10;

int n, k;
int dp[N][1 << N][N * N];
int cnt[1 << N];

void solve() {
    cin >> n >> k;

    vector<int> valid;
    for (int i = 0; i < (1 << n);++i)
        if (!(i << 1 & i) && !(i >> 1 & i)) {
            valid.emplace_back(i);
            int t = i;
            while (t) {
                cnt[i] += (t & 1);
                t >>= 1;
            }
        }

    dp[0][0][0] = 1;

    for (int i = 1;i <= n;++i) {
        for (int a : valid) {
            for (int b : valid) {
                if (!(a << 1 & b) && !(a & b) && !(a >> 1 & b)) {
                    for (int x = 0;x + cnt[a] <= k;++x)
                        dp[i][a][x + cnt[a]] += dp[i - 1][b][x];
                }
            }
        }
    }

    int ans = 0;
    for (int i : valid)
        ans += dp[n][i][k];
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
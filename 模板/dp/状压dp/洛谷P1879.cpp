#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define ld long double
#define pii pair<int,int>
#define mpair(x,y) make_pair(x,y)
#define complex complex<ld>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define PI (ld)(3.141592653589793)
#define INF (int)(1e14)
#define MOD (int)(1e8)
#define eps (ld)(1e-9)
#define P (int)(998244353)
#define G (int)(3)
#define lc p<<1
#define rc p<<1|1
// #define lc(x) tr[x].lc
// #define rc(x) tr[x].rc
// #define lc(name,x) name[x].lc
// #define rc(name,x) name[x].rc

const int N = 13;

int n, m;
int dp[N][1 << N][N * N];
int row[N];
int cnt[1 << N];

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= n;++i) {
        int val;
        for (int j = 1;j <= m;++j) {
            int t;cin >> t;
            val <<= 1;
            val += t;
        }
        row[i] = val;
    }

    vector<int> valid;
    for (int i = 0;i < (1 << m);++i) {
        if (!(i << 1 & i) && !(i >> 1 & i)) {
            valid.emplace_back(i);
            int t = i;
            while (t) {
                cnt[i] += t & 1;
                t >>= 1;
            }
        }
    }

    dp[0][0][0] = 1;

    for (int i = 1;i <= n;++i) {
        for (auto a : valid) {
            for (auto b : valid) {
                if ((a & row[i]) == a && !(a & b)) {
                    for (int k = cnt[a];k <= n * m;++k)
                        dp[i][a][k] = (dp[i][a][k] + dp[i - 1][b][k - cnt[a]]) % MOD;
                }
            }
        }
    }

    int ans = 0;
    for (int i : valid) {
        for (int j = 0;j <= n * m;++j) {
            ans += dp[n][i][j];
            ans %= MOD;
        }
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
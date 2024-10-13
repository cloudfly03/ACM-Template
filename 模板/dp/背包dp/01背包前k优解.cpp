#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define endl '\n'
#define MOD 998244353
#define INF 1e14
#define lc (p<<1)
#define rc (p<<1|1)


const int N = 201;
const int K = 51;
const int V = 5001;
int k, v, n;
int w[N], p[N];
vector<int> dp[V];

void solve() {
    cin >> k >> v >> n;
    for (int i = 1;i <= n;++i) {
        cin >> w[i] >> p[i];
    }

    dp[0].push_back(0);

    for (int i = 1;i <= n;++i) {
        for (int j = v;j >= w[i];--j) {
            for (auto elem : dp[j - w[i]]) {
                dp[j].emplace_back(elem + p[i]);
            }

            sort(all(dp[j]));
            reverse(all(dp[j]));
            while (dp[j].size() > k) dp[j].pop_back();
        }
    }

    int ans = 0;
    for (auto elem : dp[v]) {
        ans += elem;
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

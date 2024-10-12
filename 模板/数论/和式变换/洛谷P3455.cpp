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

const int N = 5e4 + 1;
int a, b, d;
int mu[N];
bool vis[N];
vector<int> primes;

void solve() {
    mu[1] = 1;
    for (int i = 2;i < N;++i) {
        if (!vis[i]) {
            mu[i] = -1;
            primes.push_back(i);
        }
        for (auto j : primes) {
            if (i * j >= N) break;
            vis[i * j] = true;
            if (i % j)
                mu[i * j] = -mu[i];
            else {
                mu[i * j] = 0;
                break;
            }
        }
    }

    for (int i = 1;i < N;++i)
        mu[i] += mu[i - 1];

    int t;cin >> t;
    while (t--) {
        cin >> a >> b >> d;
        a /= d, b /= d;
        int n = min(a, b);

        int ans = 0;
        for (int l = 1, r;l <= n;l = r + 1) {
            if (!(n / l))break;
            r = min(a / (a / l), b / (b / l));
            ans += (mu[r] - mu[l - 1]) * (a / l) * (b / l);
        }
        cout << ans << endl;
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
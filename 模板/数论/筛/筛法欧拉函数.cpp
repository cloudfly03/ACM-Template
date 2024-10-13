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

const int N = 1e6 + 1;
bool vis[N];
vector<int> primes;
int phi[N];
int n;

void solve() {
    cin >> n;
    phi[1] = 1;
    for (int i = 2;i <= n;++i) {
        if (!vis[i]) {
            phi[i] = i - 1;
            primes.emplace_back(i);
        }
        for (auto j : primes) {
            if (i * j > n) break;
            vis[i * j] = true;
            if (i % j) phi[i * j] = phi[i] * (j - 1);
            else {
                phi[i * j] = phi[i] * j;
                break;
            }
        }
    }

    for (int i = 1;i <= n;++i)
        cout << "phi[" << i << "] = " << phi[i] << endl;
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
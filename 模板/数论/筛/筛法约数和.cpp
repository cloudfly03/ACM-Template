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
int psum[N], a[N];
int n;

void solve() {
    cin >> n;
    psum[1] = 1;
    for (int i = 2;i <= n;++i) {
        if (!vis[i]) {
            psum[i] = a[i] = i + 1;
            primes.emplace_back(i);
        }
        for (auto j : primes) {
            if (i * j > n) break;
            vis[i * j] = true;
            if (i % j) {
                a[i * j] = j + 1;
                psum[i * j] = psum[i] * (j + 1);
            }
            else {
                a[i * j] = a[i] * j + 1;
                psum[i * j] = psum[i] / a[i] * a[i * j];
                break;
            }
        }
    }

    for (int i = 1;i <= n;++i)
        cout << "psum[" << i << "] = " << psum[i] << endl;
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
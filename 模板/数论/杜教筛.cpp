#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define INF (int)(1e14)
#define MOD (int)(20101009)
#define eps (ld)(1e-6)
#define lc p<<1
#define rc p<<1|1

const int N = 1e7 + 1;
vector<int> primes;
int mu[N];
int phi[N];
bool vis[N];
unordered_map<int, int> mp_phi, mp_mu;

int dfs1(int x) {
    if (x < N) return phi[x];
    if (mp_phi[x]) return mp_phi[x];
    int res = x * (x + 1) / 2;
    for (int l = 2, r;l <= x;l = r + 1) {
        if (!(x / l)) break;
        r = x / (x / l);
        res -= dfs1(x / l) * (r - l + 1);
    }
    return mp_phi[x] = res;
}

int dfs2(int x) {
    if (x < N) return mu[x];
    if (mp_mu[x]) return mp_mu[x];
    int res = 1;
    for (int l = 2, r;l <= x;l = r + 1) {
        if (!(x / l)) break;
        r = x / (x / l);
        res -= dfs2(x / l) * (r - l + 1);
    }
    return mp_mu[x] = res;
}

void solve() {
    int t;cin >> t;
    mu[1] = phi[1] = 1;
    for (int i = 2;i < N;++i) {
        if (!vis[i]) {
            mu[i] = -1;
            phi[i] = i - 1;
            primes.emplace_back(i);
        }
        for (auto j : primes) {
            if (i * j >= N) break;
            vis[i * j] = true;
            if (i % j) {
                phi[i * j] = phi[i] * (j - 1);
                mu[i * j] = -mu[i];
            }
            else {
                mu[i * j] = 0;
                phi[i * j] = phi[i] * j;
                break;
            }
        }
    }

    for (int i = 1;i < N;++i) {
        mu[i] += mu[i - 1];
        phi[i] += phi[i - 1];
    }

    while (t--) {
        int n;cin >> n;
        int ans1 = dfs1(n);
        int ans2 = dfs2(n);
        cout << ans1 << ' ' << ans2 << endl;
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
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

const int N = 1e6 + 1;
int a[N];
int n, k;
int qmin[N], hmin = 1, tmin;
int qmax[N], hmax = 1, tmax;

void solve() {
    cin >> n >> k;
    for (int i = 1;i <= n;++i) {
        cin >> a[i];
    }

    for (int i = 1;i <= n;++i) {
        if (hmin <= tmin && i - qmin[hmin] >= k) hmin++;
        while (hmin <= tmin && a[qmin[tmin]] >= a[i]) tmin--;
        qmin[++tmin] = i;
        if (hmin <= tmin && i >= k) cout << a[qmin[hmin]] << ' ';
    }
    cout << endl;

    for (int i = 1;i <= n;++i) {
        if (hmax <= tmax && i - qmax[hmax] >= k) hmax++;
        while (hmax <= tmax && a[qmax[tmax]] <= a[i]) tmax--;
        qmax[++tmax] = i;
        if (hmax <= tmax && i >= k) cout << a[qmax[hmax]] << ' ';
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

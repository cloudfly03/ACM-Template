#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define ld double
#define pii pair<int,int>
#define complex complex<ld>
#define rand mt19937_64
#define endl '\n'
#define PI (ld)(3.141592653589793)
#define INF (ld)(1e9)
#define MOD (int)(1e8)
#define eps (ld)(1e-9)
#define P (int)(998244353)
#define G (int)(3)
#define mpair(x,y) make_pair(x,y)
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)

const int N = 1e5 + 1;

int n, L;
ld a[N], ps[N];

bool judge(ld m) {
    for (int i = 1;i <= n;++i)
        ps[i] = ps[i - 1] + a[i] - m;
    ld mn = INF;
    for (int i = L;i <= n;++i) {
        mn = min(mn, ps[i - L]);
        if (ps[i] - mn >= 0) return true;
    }
    return false;
}

void solve() {
    cin >> n >> L;
    ld mn = INF, mx = 0;

    for (int i = 1;i <= n;++i) {
        cin >> a[i];
        mx = max(mx, a[i]);
        mn = min(mn, a[i]);
    }

    ld l = mn, r = mx;
    while (r - l > 1e-5) {
        ld m = (l + r) / 2;
        if (judge(m))
            l = m;
        else
            r = m;
    }
    cout << (int)(r * 1000) << endl;
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
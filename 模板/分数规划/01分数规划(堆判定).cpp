#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define complex complex<ld>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define PI (ld)(3.141592653589793)
#define INF (int)(1e14)
#define MOD (int)(1e9+9)
#define eps (ld)(1e-12)
#define P (int)(998244353)
#define G (int)(3)
#define lc p<<1
#define rc p<<1|1

const int N = 1001;
int a[N], b[N];
int n, k;


bool judge(int x) {
    priority_queue<int, vector<int>, less<int>> q;
    for (int i = 1;i <= n;++i)
        q.push(1000 * a[i] - x * b[i]);

    int ans = 0;
    int t = n - k;
    while (t--) { ans += q.top();q.pop(); }

    if (ans >= 0) return true;
    else return false;
}

void solve() {
    while (true) {
        cin >> n >> k;
        if (!n && !k) break;
        for (int i = 1;i <= n;++i) cin >> a[i];
        for (int i = 1;i <= n;++i) cin >> b[i];

        int l = 0, r = 1000;
        int ans = -1;
        while (l <= r) {
            int m = l + r >> 1;
            if (judge(m)) {
                ans = m;
                l = m + 1;
            }
            else r = m - 1;
        }
        cout << round(ans * 1.0 / 10) << endl;
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
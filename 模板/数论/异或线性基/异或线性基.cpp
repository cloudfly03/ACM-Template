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

const int N = 101;
int n;

void gauss(vector<int>& a) {
    int k = 0, n = a.size();
    for (int i = 62;i >= 0 && k < n;--i) {
        for (int j = k;j < n;++j)
            if (a[j] >> i & 1) { swap(a[j], a[k]);break; }
        if (!(a[k] >> i & 1)) continue;
        for (int j = 0;j < n;++j)
            if (j != k && (a[j] >> i & 1)) a[j] ^= a[k];
        k++;
    }
    while (a.size() > k) a.pop_back();
}

void solve() {
    cin >> n;
    vector<int> a(n);
    for (int i = 0;i < n;++i) cin >> a[i];

    gauss(a);

    int ans = 0;
    for (auto i : a)
        ans ^= i;
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
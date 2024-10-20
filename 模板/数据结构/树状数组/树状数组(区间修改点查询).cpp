#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define ld long double
#define pii pair<int,int>
#define complex complex<ld>
#define rand mt19937_64
#define endl '\n'
#define PI (ld)(3.141592653589793)
#define INF (int)(1e7+1)
#define MOD (int)(1e8)
#define eps (ld)(1e-9)
#define P (int)(998244353)
#define G (int)(3)
#define mpair(x,y) make_pair(x,y)
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)

const int N = 5e5 + 1;

int n, m;

struct TreeArr {
    int a[N];

    void update(int pos, int v) {
        for (;pos < N;pos += lowbit(pos)) a[pos] += v;
    }

    int query(int pos) {
        int ans = 0;
        for (;pos;pos -= lowbit(pos)) ans += a[pos];
        return ans;
    }
}a;

void solve() {
    cin >> n >> m;
    int last = 0;
    for (int i = 1;i <= n;++i) {
        int t;cin >> t;
        a.update(i, t - last);
        last = t;
    }

    for (int i = 1;i <= m;++i) {
        int op;cin >> op;
        if (op == 1) {//区间修改
            int x, y, k;cin >> x >> y >> k;
            a.update(x, k);
            a.update(y + 1, -k);
        }
        else {//点查询
            int x;cin >> x;
            cout << a.query(x) << endl;
        }
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
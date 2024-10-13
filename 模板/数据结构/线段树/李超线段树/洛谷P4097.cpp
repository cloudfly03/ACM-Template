#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define mpair(x,y) make_pair(x,y)
#define complex complex<ld>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define PI (ld)(3.141592653589793)
#define INF (int)(1e14)
#define MOD (int)(1e9)
#define eps (ld)(1e-9)
#define P (int)(998244353)
#define G (int)(3)
#define lc p<<1
#define rc p<<1|1
// #define lc(x) tr[x].lc
// #define rc(x) tr[x].rc
// #define lc(name,x) name[x].lc
// #define rc(name,x) name[x].rc

const int N = 1e5 + 1;
const int T = 5e4 + 1;

typedef struct {
    ld k, b;
}Line;
Line line[N];
int cnt;
int f(int id, int x) {
    return (line[id].k * x + line[id].b) / 100;
}

typedef struct {
    int id;
}SegTree;
SegTree tr[T << 2];

int n;

void update(int p, int l, int r, int L, int R, int id) {
    int m = l + r >> 1;
    if (L <= l && R >= r) {
        if (f(tr[p].id, m) < f(id, m)) swap(tr[p].id, id);
        if (f(tr[p].id, l) < f(id, l)) update(lc, l, m, L, R, id);
        if (f(tr[p].id, r) < f(id, r)) update(rc, m + 1, r, L, R, id);
        return;
    }
    if (L <= m) update(lc, l, m, L, R, id);
    if (R > m) update(rc, m + 1, r, L, R, id);
}

int query(int p, int l, int r, int x) {
    if (l == r) return f(tr[p].id, x);
    int m = l + r >> 1;
    int ans = f(tr[p].id, x);
    if (x <= m) return max(ans, query(lc, l, m, x));
    else return max(ans, query(rc, m + 1, r, x));
}

void solve() {
    cin >> n;
    for (int i = 1;i <= n;++i) {
        string op;cin >> op;
        if (op == "Project") {
            ld b, k;cin >> b >> k;
            line[++cnt].k = k;
            line[cnt].b = b - k;
            update(1, 1, T, 1, T, cnt);
        }
        else {
            int d;cin >> d;
            cout << query(1, 1, T, d) << endl;
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
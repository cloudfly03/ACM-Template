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
#define INF (ld)(1e7+1)
#define MOD (int)(1e8)
#define eps (ld)(1e-9)
#define P (int)(998244353)
#define G (int)(3)
#define mpair(x,y) make_pair(x,y)
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)

const int N = 2e5 + 1;

int n;

typedef struct {
    ld x, y;
}Point;
Point p[N];

ld dis(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

ld calc(int l, int r) {
    if (l == r) return INF;
    if (l + 1 == r) return dis(p[l], p[r]);
    int m = l + r >> 1;
    ld d = min(calc(l, m), calc(m + 1, r));

    vector<Point> x;
    for (int i = l;i <= r;++i)
        if (fabs(p[m].x - p[i].x) <= d)
            x.emplace_back(p[i]);
    sort(all(x),
        [&](Point a, Point b)->bool {
            if (a.y != b.y) return a.y < b.y;
            return a.x < b.x;
        }
    );
    for (int i = 0;i < x.size();++i)
        for (int j = i + 1;j < x.size() && (x[j].y - x[i].y < d);++j)
            d = min(d, dis(x[i], x[j]));

    return d;
}

void solve() {
    cin >> n;
    for (int i = 1;i <= n;++i)
        cin >> p[i].x >> p[i].y;

    sort(p + 1, p + n + 1,
        [&](Point a, Point b) ->bool {
            if (a.x != b.x) return a.x < b.x;
            return a.y < b.y;
        }
    );

    cout << fixed << setprecision(4) << calc(1, n) << endl;
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
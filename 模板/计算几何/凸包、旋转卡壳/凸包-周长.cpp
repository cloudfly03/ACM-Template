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
#define INF (int)(2147483647)
#define MOD (int)(1e8)
#define eps (ld)(1e-9)
#define P (int)(998244353)
#define G (int)(3)
#define mpair(x,y) make_pair(x,y)
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)

const int N = 1e5 + 1;

typedef struct {
    ld x, y;
}Point;
Point p[N];
Point andrew[N << 1];
int cnt;

bool cmp(Point a, Point b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

// a->b and a->c
ld cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

ld norm2(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int n;

void solve() {
    cin >> n;
    for (int i = 1;i <= n;++i)
        cin >> p[i].x >> p[i].y;

    sort(p + 1, p + n + 1, cmp);

    cnt = 0;
    for (int i = 1;i <= n;++i) {
        while (cnt > 1 && cross(andrew[cnt - 1], andrew[cnt], p[i]) <= 0) cnt--;
        andrew[++cnt] = p[i];
    }
    int mx = cnt;
    for (int i = n - 1;i;--i) {
        while (cnt > mx && cross(andrew[cnt - 1], andrew[cnt], p[i]) <= 0) cnt--;
        andrew[++cnt] = p[i];
    }

    ld C = 0;
    for (int i = 1;i < cnt;++i)
        C += norm2(andrew[i], andrew[i + 1]);
    cout << C << endl;
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
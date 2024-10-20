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

// 让整个平面的点绕原点旋转随机角度,对x进行排序，每次只取后5个点计算

int n;

typedef struct {
    ld x, y;
}Point;
Point p[N];
rand rnd(clock());

ld dis(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void rotate(Point& a, ld theta) {
    ld x = a.x, y = a.y;
    a.x = cos(theta) * x - sin(theta) * y;
    a.y = sin(theta) * x + cos(theta) * y;
}

void solve() {
    cin >> n;
    for (int i = 1;i <= n;++i)
        cin >> p[i].x >> p[i].y;
    int random = rnd();
    ld theta = random - floor(random / PI) * PI;
    for (int i = 1;i <= n;++i)
        rotate(p[i], theta);
    sort(p + 1, p + n + 1,
        [&](Point a, Point b) -> bool {
            return a.x < b.x;
        }
    );

    ld ans = INF;
    for (int i = 1;i <= n;++i)
        for (int j = 1;j <= 5 && i + j <= n;++j)
            ans = min(ans, dis(p[i], p[i + j]));

    cout << fixed << setprecision(4) << ans << endl;
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
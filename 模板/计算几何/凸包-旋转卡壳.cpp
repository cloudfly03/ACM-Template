#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define endl ('\n')
const int INF = 1e14;
const int MOD = 1e9 + 7;

const int N = 50005;
typedef struct {
    int x, y;
}Point;
Point p[N];
int n;
Point andrew[N];
int cnt;


int cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

int len(Point a, Point b) {
    return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
}

bool cmp(Point a, Point b) {
    if (a.x != b.x)return a.x < b.x;
    return a.y < b.y;
}

void solve() {
    cin >> n;
    for (int i = 1;i <= n;++i) {
        cin >> p[i].x >> p[i].y;
    }
    sort(p + 1, p + n + 1, cmp);

    cnt = 0;
    for (int i = 1;i <= n;++i) {
        while (cnt > 1 && cross(andrew[cnt - 1], andrew[cnt], p[i]) <= 0) cnt--;
        andrew[++cnt] = p[i];
    }
    int mx = cnt;
    for (int i = n - 1;i > 0;--i) {
        while (cnt > mx && cross(andrew[cnt - 1], andrew[cnt], p[i]) <= 0) cnt--;
        andrew[++cnt] = p[i];
    }

    int ans = 0;
    cnt--;
    for (int i = 1, j = 2;i <= cnt;++i) {
        while (cross(andrew[i], andrew[i + 1], andrew[j]) < cross(andrew[i], andrew[i + 1], andrew[j + 1])) j = j % cnt + 1;
        ans = max({ ans, len(andrew[i],andrew[j]),len(andrew[i + 1],andrew[j]) });
    }
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
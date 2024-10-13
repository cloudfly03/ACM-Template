#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define endl ('\n')
const int INF = 1e14;
const int MOD = 1e9 + 7;

const int N = 1.1e7 + 10;
char s[N];
char t[N << 1];
int ans[N << 1];

void solve() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    int k = 1;t[k] = '#';
    for (int i = 1;i <= n;++i) {
        t[++k] = s[i];
        t[++k] = '#';
    }
    n = k;

    for (int i = 1, l, r = 0;i <= n;++i) {
        if (i <= r) ans[i] = min(r - i + 1, ans[l + r - i]);
        while (i + ans[i] <= n && i - ans[i] > 0 && t[i + ans[i]] == t[i - ans[i]]) ans[i]++;
        if (i + ans[i] - 1 > r) l = i - ans[i] + 1, r = i + ans[i] - 1;
    }
    int ret = 0;
    for (int i = 1;i <= n;++i) {
        if (t[i] == '#') {
            ret = max(ret, ans[i] / 2 * 2);
        }
        else {
            ret = max(ret, (ans[i] - 1) / 2 * 2 + 1);
        }
    }
    cout << ret << endl;
}

signed main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);

    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}
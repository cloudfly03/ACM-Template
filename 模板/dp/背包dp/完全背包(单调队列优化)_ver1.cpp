#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define endl ('\n')
const int INF = 1e14;
const int MOD = 1e9 + 7;

const int N = 2e4 + 1;

int n, m;
int f[2][N];

//使用双端队列模拟单调队列 常数比较大

void solve() {
    cin >> n >> m;

    for (int i = 1;i <= n;++i) {
        int v, w, s;cin >> v >> w >> s;
        for (int j = 0;j < v;++j) {
            deque<int> q;
            for (int k = j;k <= m;k += v) {
                if (!q.empty() && k - q.front() > v * s) q.pop_front();
                if (!q.empty()) f[i & 1][k] = max(f[!(i & 1)][k], f[!(i & 1)][q.front()] + (k - q.front()) / v * w);
                while (!q.empty() && ((k - q.back()) / v * w <= f[!(i & 1)][k] - f[!(i & 1)][q.back()])) q.pop_back();
                q.push_back(k);
            }
        }
    }

    cout << f[n & 1][m] << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}


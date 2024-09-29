#include<bits/stdc++.h>
#include<iomanip>
#define int long long
#define endl '\n'
#define mset multiset
#define PII pair<int,int>
#define N 150606
#define lc p<<1.
#define rc p<<1|1
#define x first
#define y second
//#define lb long double
#define pb(x) push_back(x)
//#define ll long long
using namespace std;
int vis[N];
int n, m;
int ans;
vector<int>v[N];
void bfs(int x) {
    for (int i = 1; i <= n; ++i)vis[i] = 0;
    queue<PII>q;
    q.push({ x,1 });
    vis[x] = 1;
    while (q.size()) {
        PII top = q.front();
        q.pop();
        int x = top.x;
        int sd = top.y;
        ans = max(ans, sd);
        for (auto y : v[x]) {
            if (vis[y])continue;
            q.push({ y,sd + 1 });
            vis[y] = 1;
        }
    }
}
void solve() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    for (int i = 1; i <= n; ++i) {
        bfs(i);
    }
    cout << ans;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //	int T;cin>>T;
    //	while(T--)
    solve();
}
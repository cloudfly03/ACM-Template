#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define INF 1e14
#define MOD 998244353
#define endl '\n'


const int N = 2e4 + 10;
const int M = 160;

int trie[N][26], cnt[N], tot;
int mp[N];
int nxt[N];
string tar[M];
int n;

void init() {
    for (int i = 0;i <= tot;++i) {
        fill(trie[i], trie[i] + 26, 0);
    }
    fill(cnt, cnt + tot + 1, 0);
    fill(nxt, nxt + tot + 1, 0);
    fill(tar, tar + n + 1, 0);
    fill(mp, mp + tot + 1, 0);
    tot = 0;
}

void solve() {
    while (true) {
        init();
        cin >> n;
        if (n == 0) break;
        for (int i = 1;i <= n;++i) {
            cin >> tar[i];
            int p = 0;
            for (auto ch : tar[i]) {
                if (!trie[p][ch - 'a']) trie[p][ch - 'a'] = ++tot;
                p = trie[p][ch - 'a'];
            }
            cnt[p]++;
            mp[p] = i;
        }

        queue<int> q;
        for (int i = 0;i < 26;++i) {
            if (trie[0][i]) q.push(trie[0][i]);
        }
        while (q.size()) {
            int u = q.front();q.pop();
            for (int i = 0;i < 26;++i) {
                int v = trie[u][i];
                if (v) { nxt[v] = trie[nxt[u]][i], q.push(v); }
                else trie[u][i] = trie[nxt[u]][i];
            }
        }

        int ans[M]{};
        int mx = 0;
        string t;cin >> t;
        for (int i = 0, j = 0;i < t.size();++i) {
            j = trie[j][t[i] - 'a'];
            for (int k = j;k;k = nxt[k]) {
                ans[mp[k]] += cnt[k];
                mx = max(ans[mp[k]], mx);
            }
        }

        cout << mx << endl;
        for (int i = 1;i <= n;++i) {
            if (ans[i] == mx) cout << tar[i] << endl;
        }
    }
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}
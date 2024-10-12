#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define complex complex<ld>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define PI (ld)(3.141592653589793)
#define INF (int)(1e14)
#define MOD (int)(998244353)
#define eps (ld)(1e-12)
#define P (int)(998244353)
#define G (int)(3)
#define lc p<<1
#define rc p<<1|1

int qpow(int base, int p) {
    int ans = 1;
    while (p) {
        if (p & 1) ans = ans * base % P;
        base = base * base % P;
        p >>= 1;
    }
    return ans;
}

int inv(int x) {
    return qpow(x, P - 2);
}

void NTT(vector<int>& A, bool rev) {
    int n = A.size();
    if (n == 1) return;
    vector<int> A1(n / 2), A2(n / 2);
    for (int i = 0;i < n / 2;++i)
        A1[i] = A[i * 2], A2[i] = A[i * 2 + 1];
    NTT(A1, rev);NTT(A2, rev);
    int g1 = qpow((rev ? inv(G) : G), (P - 1) / A.size());
    int gk = 1;
    for (int i = 0;i < n / 2;++i) {
        A[i] = (A1[i] + A2[i] * gk % P) % P;
        A[i + n / 2] = ((A1[i] - A2[i] * gk % P) % P + P) % P;
        gk = gk * g1 % P;
    }
}

vector<int> multiply_polynomials(const vector<int>& a, const vector<int>& b) {
    int n = 1, ni;
    while (n < a.size() + b.size()) n <<= 1;
    ni = inv(n);
    vector<int> A(n), B(n);
    for (int i = 0;i < a.size();++i) A[i] = (a[i] % P + P) % P;
    for (int i = 0;i < b.size();++i) B[i] = (b[i] % P + P) % P;
    NTT(A, 0);NTT(B, 0);
    for (int i = 0;i < n;++i) A[i] = A[i] * B[i] % P;
    NTT(A, 1);
    vector<int> ans(a.size() + b.size() - 1);
    for (int i = 0;i < a.size() + b.size() - 1;++i)
        ans[i] = A[i] * ni % P;
    return ans;
}

int n, m;

void solve() {
    cin >> n >> m;
    vector<int> a(n + 1), b(m + 1);
    for (int i = 0;i <= n;++i)cin >> a[i];
    for (int i = 0;i <= m;++i)cin >> b[i];
    vector<int> ans = multiply_polynomials(a, b);
    for (auto v : ans)
        cout << v << ' ';
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
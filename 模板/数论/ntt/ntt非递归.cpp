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

void FFT(vector<int>& A, const vector<int>& R, bool rev) {
    int n = A.size();
    for (int i = 0;i < n;++i)
        if (i < R[i]) swap(A[i], A[R[i]]);
    for (int m = 2;m <= n;m <<= 1) {
        int g1 = qpow(rev ? inv(G) : G, (P - 1) / m);
        for (int i = 0;i < n;i += m) {
            int gk = 1;
            for (int j = 0;j < m / 2;++j) {
                int x = A[i + j], y = A[i + j + m / 2] * gk % P;
                A[i + j] = (x + y) % P;
                A[i + j + m / 2] = (x - y + P) % P;
                gk = gk * g1 % P;
            }
        }
    }
}

vector<int> multiply_polynomials(const vector<int>& a, const vector<int>& b) {
    int n = 1, ni;
    while (n < a.size() + b.size()) n <<= 1;
    ni = inv(n);
    vector<int> A(n), B(n), R(n);
    for (int i = 0;i < n;++i) R[i] = R[i / 2] / 2 + (i & 1 ? n / 2 : 0);
    for (int i = 0;i < a.size();++i) A[i] = a[i];
    for (int i = 0;i < b.size();++i) B[i] = b[i];
    FFT(A, R, 0);FFT(B, R, 0);
    for (int i = 0;i < n;++i) A[i] = A[i] * B[i] % P;
    FFT(A, R, 1);
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
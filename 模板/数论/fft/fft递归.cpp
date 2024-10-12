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
#define MOD (int)(1e9+7)
#define eps (ld)(1e-12)
#define lc p<<1
#define rc p<<1|1

void FFT(vector<complex>& A, bool rev) {
    int n = A.size();
    if (n == 1) return;
    vector<complex> A1(n / 2), A2(n / 2);
    for (int i = 0;i < n / 2;++i)
        A1[i] = A[i * 2], A2[i] = A[i * 2 + 1];
    FFT(A1, rev);FFT(A2, rev);
    complex w1(cos(2 * PI / n), (rev ? -1 : 1) * sin(2 * PI / n));
    complex wk(1, 0);
    for (int i = 0;i < n / 2;++i) {
        A[i] = A1[i] + A2[i] * wk;
        A[i + n / 2] = A1[i] - A2[i] * wk;
        wk = wk * w1;
    }
}

vector<int> multiply_polynomials(const vector<int>& a, const vector<int>& b) {
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    vector<complex> A(n), B(n);
    for (int i = 0;i < a.size();++i) A[i] = a[i];
    for (int i = 0;i < b.size();++i) B[i] = b[i];
    FFT(A, 0);FFT(B, 0);
    for (int i = 0;i < n;++i) A[i] = A[i] * B[i];
    FFT(A, 1);
    vector<int> ans(a.size() + b.size() - 1);
    for (int i = 0;i < a.size() + b.size() - 1;++i)
        ans[i] = round(A[i].real() / n);
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
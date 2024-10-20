
# 组合数
## 递推式预处理

- 初始化 $ C_{0}^{0} $ ~ $ C_{n}^{n} $
- 时间复杂度 $ O(n^{2}) $ 、空间复杂度 $ O(n^{2}) $
- 查询复杂度 $ O(1) $

```cpp {.line-numbers}
int C[N][N];

void init(){
    for (int i = 0;i < N;++i)
        for (int j = 0;j <= i;++j) {
            if (j == 0) C[i][j] = 1;
            else C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
        }
}
```

## 递推式记忆化

- 计算 $ C_{n}^{m} $
- 时间复杂度 $ O(n^{2}) $ 、空间复杂度 $ O(n^{2}) $
- 查询平均复杂度 $ O(1) $

```cpp {.line-numbers}
int res[N][N];

int C(int n, int m) {
    if (m == 0 || m == n) return 1;
    if (m > (n >> 1)) m = n - m;
    if (res[n][m]) return res[n][m];
    return res[n][m] = (C(n - 1, m) + C(n - 1, m - 1)) % MOD;
}
```

##
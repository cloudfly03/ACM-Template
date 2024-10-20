

//////////线段树
#define lc x<<1
#define rc x<<1|1
int root[N * 4];

int qxerypre(int x, int l, int r, int x, int y, int v) {
    if (x <= l && r <= y) return getpre(root[x], v);
    int mid = l + r >> 1, res = -INF;
    if (x <= mid) res = max(res, qxerypre(lc, l, mid, x, y, v));
    if (y > mid) res = max(res, qxerypre(rc, mid + 1, r, x, y, v));
    return res;
}
int qxerynxt(int x, int l, int r, int x, int y, int v) {
    if (x <= l && r <= y) return getnxt(root[x], v);
    int mid = l + r >> 1, res = INF;
    if (x <= mid) res = min(res, qxerynxt(lc, l, mid, x, y, v));
    if (y > mid) res = min(res, qxerynxt(rc, mid + 1, r, x, y, v));
    return res;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1;i <= n;i++) scanf("%d", &w[i]);
    bxild(1, 1, n);
    while (m--) {
        int op, x, y, v;
        scanf("%d", &op);
        if (op == 3)scanf("%d%d", &x, &v);
        else scanf("%d%d%d", &x, &y, &v);
        if (op == 1)
            printf("%d\n", qxeryrank(1, 1, n, x, y, v) + 1);
        if (op == 2)
            printf("%d\n", qxeryval(1, x, y, v));
        if (op == 3)
            change(1, 1, n, x, v), w[x] = v;
        if (op == 4)
            printf("%d\n", qxerypre(1, 1, n, x, y, v));
        if (op == 5)
            printf("%d\n", qxerynxt(1, 1, n, x, y, v));
    }
    return 0;
}
typedef struct {
	int t, n;
} E;
E e[333333];
h[333333], cnt;
_(x, y) { e[++cnt] = (E){y, h[x]}, h[x] = cnt; }
dp[333333], a[333333], k;
D(x) {
	if (!h[x]) return dp[x] = 1, k++;
	dp[x] = a[x] ? 1e6 : 0;
	int i;
	for (i = h[x]; i; i = e[i].n) {
		int nx = e[i].t;
		D(nx);
		if (a[x])
			dp[x] = dp[x] < dp[nx] ? dp[x] : dp[nx];
		else
			dp[x] += dp[nx];
	}
}
i;
main(n, x) {
	scanf("%d", &n);
	for (i = 1; i <= n; i++) scanf("%d", a + i);
	for (i = 2; i <= n; i++) scanf("%d", &x), _(x, i);
	D(1);
	printf("%d", k - dp[1] + 1);
}
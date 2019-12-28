typedef long long l;
l a[111111], b[111111], dp[111111][3];
l max(l a, l b) { return a > b ? a : b; }
main(n, i) {
	scanf("%d", &n);
	for (i = 1; i <= n; i++) scanf("%lld", a + i);
	for (i = 1; i <= n; i++) scanf("%lld", b + i);
	for (i = 1; i <= n; i++) {
		dp[i][0] = max(dp[i - 1][1], dp[i - 1][2]) + a[i];
		dp[i][1] = max(dp[i - 1][0], dp[i - 1][2]) + b[i];
		dp[i][2] = max(dp[i - 1][0], max(dp[i - 1][1], dp[i - 1][2]));
	}
	printf("%lld", max(dp[n][0], max(dp[n][1], dp[n][2])));
}
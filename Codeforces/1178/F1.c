const p = 998244353;
a[555], dp[555][555];
main(n, m, i, l, r, k, t, la, ra) {
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; i++) scanf("%d", a + i), dp[i][i] = dp[i][i - 1] = 1;
	dp[n + 1][n] = 1;
	for (k = 2; k <= n; k++)
		for (l = 1, r = l + k - 1; r <= n; l++, r++) {
			la = ra = 0;
			for (t = i = l; i <= r; i++) t = a[i] < a[t] ? i : t;
			for (i = l; i <= t; i++) la = (la + 1ll * dp[l][i - 1] * dp[i][t - 1]) % p;
			for (i = t; i <= r; i++) ra = (ra + 1ll * dp[t + 1][i] * dp[i + 1][r]) % p;
			dp[l][r] = 1ll * la * ra % p;
		}
	printf("%d", dp[1][n]);
}
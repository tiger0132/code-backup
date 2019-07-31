a[111111];
main(n, x, y, i, j, mn) {
	scanf("%d%d%d", &n, &x, &y);
	for (i = 1; i <= n; i++) scanf("%d", a + i);
	for (i = 1; i <= n; i++) {
		mn = 1e9;
		for (j = i - 1; j >= 1 && j >= i - x; j--) mn = a[j] < mn ? a[j] : mn;
		for (j = i + 1; j <= n && j <= i + y; j++) mn = a[j] < mn ? a[j] : mn;
		if (mn > a[i]) return !printf("%d", i);
	}
}
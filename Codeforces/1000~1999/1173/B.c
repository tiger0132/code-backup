main(n, m, i) {
	scanf("%d", &n);
	printf("%d\n", m = (n + 2) / 2);
	for (i = 1; i <= n && i <= m; i++) printf("%d %d\n", 1, i);
	for (i = 1; i <= n - m; i++) printf("%d %d\n", i + 1, m);
}
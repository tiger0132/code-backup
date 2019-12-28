n;
id(i, j) { return (i - 1) * n + j; }
main(i, j) {
	scanf("%d", &n);
	for (i = 1; i <= n / 2; i++) {
		for (j = 1; j <= n; j++)
			printf("%d%c", id(j, j % 2 ? i : n - i + 1), " \n"[j == n]);
		for (j = 1; j <= n; j++)
			printf("%d%c", id(j, j % 2 ? n - i + 1 : i), " \n"[j == n]);
	}
	if (n % 2)
		for (j = 1; j <= n; j++) printf("%d%c", id(j, n / 2 + 1), " \n"[j == n]);
}
f[555], a[111], b[111];
main(n, m, i, j) {
	scanf("%d", &n);
	for (i = 0; i < n; i++) scanf("%d", a + i), a[i][f] = 1;
	scanf("%d", &m);
	for (i = 0; i < m; i++) scanf("%d", b + i), b[i][f] = 1;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			if (!f[a[i] + b[j]]) return !printf("%d %d", a[i], b[j]);
}
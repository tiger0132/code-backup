a[111], b[111], c[111][111];
main(n, m, h, i, j) {
	scanf("%d%d%d", &n, &m, &h);
	for (i = 1; i <= m; i++) scanf("%d", b + i);
	for (i = 1; i <= n; i++) scanf("%d", a + i);
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			scanf("%d", c[i] + j);
			printf("%d%c", c[i][j] * (a[i] < b[j] ? a[i] : b[j]), " \n"[j == m]);
		}
	}
}
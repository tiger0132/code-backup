a[222222], b[222222], x, c;
main(n, i, j) {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		for (i = 1; i <= n; i++) scanf("%d", a + i);
		for (i = 1; i <= n; i++) {
			if (b[i]) {
				printf("%d%c", b[i], " \n"[i == n]);
				continue;
			}
			for (j = i, c = 1; a[j] != i; j = a[j]) c++;
			for (j = i; a[j] != i; j = a[j]) b[j] = c;
			printf("%d%c", c, " \n"[i == n]);
		}
		memset(b, 0, 4 * (n + 2));
	}
}
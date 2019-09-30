a[1111], b[1111], f[1111][1111], p = 1e9 + 7, aa;
pw(x, y) {
	int r = 1;
	for (; y; y >>= 1, x = 1ll * x * x % p)
		if (y & 1) r = 1ll * r * x % p;
	return r;
}
main(n, m, i, j) {
	memset(f, -1, sizeof f);
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; i++) {
		scanf("%d", a + i);
		for (j = 1; j <= a[i]; j++) {
			if (f[i][j] != -1 && f[i][j] != 1) return puts("0"), 0;
			f[i][j] = 1;
		}
		if (f[i][a[i] + 1] != -1 && f[i][a[i] + 1]) return puts("0"), 0;
		f[i][a[i] + 1] = 0;
	}
	for (i = 1; i <= m; i++) {
		scanf("%d", b + i);
		for (j = 1; j <= b[i]; j++) {
			if (f[j][i] != -1 && f[j][i] != 1) return puts("0"), 0;
			f[j][i] = 1;
		}
		if (f[b[i] + 1][i] != -1 && f[b[i] + 1][i]) return puts("0"), 0;
		f[b[i] + 1][i] = 0;
	}
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++) aa += -1 == f[i][j];
	printf("%d", pw(2, aa));
}
x, s;
main(n, i, j) {
	for (scanf("%*d"); ~scanf("%d", &n); s = 0) {
		for (i = 0; i < n; i++) scanf("%d", &x), s += x;
		printf("%d\n", (s + n - 1) / n);
	}
}
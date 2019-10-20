a[2], b[2];
main(n, m, x) {
	for (scanf("%*d"); a[0] = a[1] = b[0] = b[1] = 0, ~scanf("%d", &n);) {
		for (; n--; a[x % 2]++) scanf("%d", &x);
		for (scanf("%d", &m); m--; b[x % 2]++) scanf("%d", &x);
		printf("%lld\n", 1ll * a[0] * b[0] + 1ll * a[1] * b[1]);
	}
}
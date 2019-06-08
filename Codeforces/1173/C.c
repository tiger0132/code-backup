a[222222], b[222222], bp[222222], p1, m;
main(n, i, x, ub) {
	scanf("%d", &n);
	for (i = 1; i <= n; i++) scanf("%d", &x), a[x] = 1;
	for (i = 1; i <= n; i++) {
		scanf("%d", b + i);
		bp[b[i]] = i;
	}
	p1 = bp[1];
	if (p1) {
		// round 1
		m = n - p1 + 1;
		for (i = p1; i <= n; i++)
			if (b[i] != i - p1 + 1) {
				m = 0;
				break;
			}
		for (i = m + 1; i <= n; i++)
			if (bp[i] >= i - m) {
				m = 0;
				break;
			}
		if (m) return !printf("%d", n - m);
	}
	// round 2
	ub = 0;
	for (i = 1; i <= n; i++)
		if (bp[i] - i + 1 > ub) ub = bp[i] - i + 1;
	printf("%d", n + ub);
}
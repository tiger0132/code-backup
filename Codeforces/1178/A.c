a[111], s, s2, b[111], t;
main(n, i) {
	scanf("%d%d", &n, a + 1);
	b[++t] = 1, s = s2 = a[1];
	for (i = 2; i <= n; i++) {
		scanf("%d", a + i);
		if (a[i] * 2 <= a[1]) b[++t] = i, s += a[i];
		s2 += a[i];
	}
	if (s * 2 <= s2) return puts("0"), 0;
	printf("%d\n", t);
	for (i = 1; i <= t; i++) printf("%d ", b[i]);
}
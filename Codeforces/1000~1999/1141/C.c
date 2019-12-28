n, a[400005], b[400005], *f = b + 200002, i, d, lo, hi;
main() {
	scanf("%d", &n);
	f[0] = 1;
	for (i = 1; i < n; i++) {
		scanf("%d", a + i);
		d += a[i];
		if (f[d]) return !printf("-1");
		f[d] = 1;
		lo = lo < d ? lo : d;
		hi = hi > d ? hi : d;
	}
	if (hi - lo + 1 != n) return !printf("-1");
	d = 0;
	printf("%d", -lo + 1);
	for (i = 1; i < n; i++) {
		printf(" %d", -lo + 1 + (d += a[i]));
	}
}
long long h, n, s, a[200005], i, b = 1e18, c, hi;
main() {
	scanf("%lld%lld", &h, &n);
	for (i = 0; i < n; i++) {
		scanf("%lld", a + i), a[i] += !!i * a[i - 1], hi = hi > -a[i] ? hi : -a[i];
		if (h + a[i] <= 0) return !printf("%d", i + 1);
	}
	s = -a[n - 1];
	if (hi <= 0 || s <= 0) return !printf("-1");
	for (i = 0; i < n; i++) {
		c = (h + a[i] + s - 1) / s * n + i + 1;
		b = b < c ? b : c;
	}
	printf("%lld", b);
}
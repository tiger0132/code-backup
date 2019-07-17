typedef long long l;
const l p = 998244353;
l a[111111], b[111111], ans;
l f(l x, l y) {
	if (x > 9) return (f(x / 10, y - 1) * (y > 0 ? 100 : 10) + x % 10) % p;
	return x % 10;
}
main(n, i, j, k) {
	scanf("%d", &n);
	for (i = 1; i <= n; i++) scanf("%lld", a + i), b[i] = (int)log10(a[i]) + 1;
	for (i = 1; i <= 10; i++)
		for (j = 1; j <= 10; j++) {
			int c1 = 0, c2 = 0, w = i < j ? i - 1 : j - 1;
			l a1 = 0, a2 = 0;
			for (k = 1; k <= n; k++) {
				if (b[k] == i) a1 = (a1 + f(a[k], w) * 10) % p, c1++;
				if (b[k] == j) a2 = (a2 + f(a[k], w + 1)) % p, c2++;
			}
			ans = (ans + a1 * c2 % p + a2 * c1 % p) % p;
		}
	printf("%lld", ans);
}
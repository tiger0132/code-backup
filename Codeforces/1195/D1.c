typedef long long l;
const l p = 998244353;
l a[111111], ans;
l f(l x) {
	if (x > 9) return (f(x / 10) * 100 + x % 10) % p;
	return x % 10;
}
main(n, i) {
	scanf("%d", &n);
	for (i = 1; i <= n; i++) scanf("%lld", a + i), ans = (ans + f(a[i]) * 11) % p;
	printf("%lld", ans * n % p);
}
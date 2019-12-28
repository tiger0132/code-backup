typedef long long l;
l n, k, m, u, c;
main() {
	scanf("%lld%lld", &n, &k);
	m = (sqrt(8 * k + 1) - 1) / 2 - 5;
	m = m < 0 ? 0 : m;
	for (;; m++)
		if (m * (m + 1) / 2 - n + m == k) return !printf("%lld", n - m);
}
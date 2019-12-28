long long gcd(long long a, long long b) { return b ? gcd(b, a % b) : a; }
long long n, m, q, x, u1, v1, u2, v2;
main() {
	scanf("%lld%lld%lld", &n, &m, &q);
	for (x = gcd(n, m); q--;) {
		scanf("%lld%lld%lld%lld", &u1, &v1, &u2, &v2), v1--, v2--;
		int p, q;
		if (u1 == 1) p = v1 / (n / x);
		if (u1 == 2) p = v1 / (m / x);
		if (u2 == 1) q = v2 / (n / x);
		if (u2 == 2) q = v2 / (m / x);
		puts(p == q ? "YES" : "NO");
	}
}
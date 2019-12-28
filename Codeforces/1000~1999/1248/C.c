f[111111], g[111111], p = 1e9 + 7;
main(n, m, i, j) {
	scanf("%d%d", &n, &m);
	if (n > m) i = n, n = m, m = i;
	f[1] = g[1] = 1;
	for (i = 2; i <= m + 1; i++)
		f[i] = (g[i - 1] + g[i - 2]) % p, g[i] = (f[i - 1] + f[i - 2]) % p;
	printf("%lld", (1ll * f[m + 1] + g[m + 1] + f[n + 1] + g[n + 1] + p - 2) % p);
}
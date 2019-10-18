r, p = 1e9 + 7;
pw(x, y) {
	for (r = 1; y; y >>= 1, x = 1ll * x * x % p)
		if (y & 1) r = 1ll * r * x % p;
	return r;
}
main(n, m) {
	scanf("%d%d", &n, &m);
	printf("%d", pw(pw(2, m) - 1, n));
}
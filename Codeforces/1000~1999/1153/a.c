n, k, x, y, i, l = 1e6, a;
main() {
	scanf("%d%d", &n, &k);
	for (i = 1; i <= n; i++) {
		scanf("%d%d", &x, &y);
		while (x < k) x += y;
		if (x < l) l = x, a = i;
	}
	printf("%d", a);
}
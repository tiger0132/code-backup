a[111], f[111], x, b;
main(n, i) {
	scanf("%d", &n);
	for (i = 0; i < n; i++) scanf("%d", a + i);
	for (;; b++) {
		x = 1e9;
		for (i = 0; i < n; i++)
			if (a[i] < x && !f[i]) x = a[i];
		if (x == 1e9) return !printf("%d", b);
		for (i = 0; i < n; i++)
			if (a[i] % x == 0) f[i] = 1;
	}
}
a, b, x;
main(n, i, l) {
	scanf("%d", &n);
	a++;
	for (i = 0, l = 1; i < n; i++) {
		scanf("%d", &x);
		x > 0 ? x = 1 : (x = -1);
		l *= x;
		l > 0 ? a++ : b++;
	}
	printf("%lld %lld", 1ll * a * b, 1ll * a * (a - 1) / 2 + 1ll * b * (b - 1) / 2);
}
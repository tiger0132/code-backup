main(n, a, i) {
	scanf("%d", &n);
	for (i = a = 1; i < n; i++) a += 4 * i;
	printf("%d", a);
}
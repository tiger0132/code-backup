n, i, j, k = 500;
f(x) { return x > n ? x - k : x; }
main() {
	scanf("%d", &n);
	if (n <= k) {
		printf("%d", n);
		for (i = n + 1; puts(""), --i;)
			for (j = n; j--;) printf("%d ", i);
		return 0;
	}
	puts("500");
	for (i--; ++i < k; puts(""))
		for (j = 0; j < k; j++) printf("%d ", f((i + j) % k + 1 + j % 2 * k));
}
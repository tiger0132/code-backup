n, a[400005], b, c, i;
main() {
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", a + i);
		a[i + n] = a[i];
	}
	for (i = 0; i < 2 * n; i++) {
		if (a[i] == 0) {
			c = c > b ? c : b;
			b = 0;
		} else
			b++;
	}
	c = c > b ? c : b;
	printf("%d", c);
}
n, i, t, x, y, a[111], b[111];
char s[111];
main() {
	scanf("%d%s", &n, s);
	for (i = 0; i < n; i++) scanf("%d%d", a + i, b + i);
	for (t = 0; t < 1000; t++) {
		x = 0;
		for (i = 0; i < n; i++) {
			if (t < b[i])
				x += s[i] == '1';
			else
				x += ((t - b[i]) / a[i] % 2) ^ (s[i] == '0');
		}
		y = x > y ? x : y;
	}
	printf("%d", y);
}
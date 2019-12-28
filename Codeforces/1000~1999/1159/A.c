char s[111];
n, x, i, a;
main() {
	scanf("%d%s", &n, s);
	for (i = 0; i < n; i++) {
		x += s[i] == '+' ? 1 : -1;
		x > a && (a = x);
		x < 0 && (x = 0);
	}
	printf("%d", x);
}
char s[1111111], t[1111111];
n, m, i, c, a0, a;
main() {
	scanf("%s%s", s, t);
	n = strlen(s), m = strlen(t);
	for (i = 1; i < m; i++) c ^= t[i] != t[i - 1];
	for (i = 0; i < m; i++) a0 ^= s[i] != t[i];
	a = !a0;
	for (i = 1; i <= n - m; i++) {
		a0 ^= c ^ (t[0] != s[i - 1]) ^ (s[i + m - 1] ^ t[m - 1]);
		a += !a0;
	}
	printf("%d", a);
}
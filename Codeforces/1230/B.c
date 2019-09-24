char s[222222];
main(n, k, i) {
	scanf("%d%d%s", &n, &k, s);
	if (!k) return puts(s), 0;
	if (n == 1) return puts("0"), 0;
	if (*s != '1') *s = '1', k--;
	for (i = 1; i < n && k; i++)
		if (s[i] != '0') s[i] = '0', k--;
	puts(s);
}
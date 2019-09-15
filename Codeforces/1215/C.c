char s[222222], t[222222];
aa[222222], bb[222222], a, b;
main(n, i) {
	scanf("%d%s%s", &n, s, t);
	for (i = 0; i < n; i++)
		if (s[i] != t[i]) {
			if (s[i] == 'a')
				aa[a++] = i;
			else
				bb[b++] = i;
		}
	if ((a + b) % 2) return puts("-1"), 0;
	printf("%d\n", a / 2 + b / 2 + (a % 2) * 2);
	for (int i = 0; i < a - 1; i += 2) printf("%d %d\n", 1 + aa[i], 1 + aa[i + 1]);
	for (int i = 0; i < b - 1; i += 2) printf("%d %d\n", 1 + bb[i], 1 + bb[i + 1]);
	if (a % 2)
		printf("%d %d\n%d %d", 1 + bb[a - 1], 1 + bb[a - 1], 1 + aa[a - 1],
			   1 + bb[a - 1]);
}
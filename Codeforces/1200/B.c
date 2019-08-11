a[111];
main(n, m, k, i, x) {
	for (scanf("%*d"); ~scanf("%d%d%d", &n, &m, &k);) {
		for (i = 0; i < n; i++) scanf("%d", a + i);
		for (i = 1; i < n; i++) {
			if (a[i - 1] + m + k < a[i]) {
				puts("NO");
				goto end;
			}
			x = a[i] - a[i - 1] - k;
			m += a[i - 1] < -x ? a[i - 1] : -x;
		}
		puts("YES");
	end:;
	}
}
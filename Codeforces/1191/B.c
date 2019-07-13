char s[22][22], c, _s[] = "mps";
a[22][22], ans;
main(i, j, t, ty, ans2, k) {
	for (i = 1; i <= 3; i++) {
		scanf("%s", s[i]);
		t = s[i][0] - 48, c = s[i][1];
		if (c == 'm') ty = 1;
		if (c == 'p') ty = 2;
		if (c == 's') ty = 3;
		a[t][ty]++;
	}
	for (i = 1; i <= 9; i++)
		for (j = 1; j <= 3; j++)
			if (a[i][j] > ans) ans = a[i][j];
	if (ans == 3) return puts("0"), 0;
	ans2 = 3 - ans, ans = 0;
	for (j = 1; j <= 3; j++)
		for (i = 1; i <= 7; i++) {
			for (k = i; k <= i + 2; k++)
				if (a[k][j] > 1) a[k][j] = 1;
			int tt = a[i][j] + a[i + 1][j] + a[i + 2][j];
			if (tt > ans) ans = tt;
		}
	ans = 3 - ans;
	printf("%d", ans < ans2 ? ans : ans2);
}
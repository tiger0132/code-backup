char a[2][222222];
n;
dfs(x, y, dir) {
	// printf("(%d, %d, %d)\n", x, y, dir);
	if (x < 0 || y < 0 || x > 1 || y >= n) return 0;
	if (x == 1 && y == n - 1) return (dir && a[x][y] < '3') || (!dir && a[x][y] >= '3');
	if (!x && !y) {
		if (a[x][y] < '3')
			return dfs(0, 1, 1);
		else
			return dfs(1, 0, 0);
	}
	if (a[x][y] < '3') {
		if (dir != 1) return 0;
		return dfs(x, y + 1, 1);
	}
	if (!dir || dir == 2) return dfs(x, y + 1, 1);
	if (dir == 1) {
		if (!x) return dfs(x + 1, y, 0);
		return dfs(x - 1, y, 2);
	}
}
main() {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		scanf("%s%s", a[0], a[1]);
		puts(dfs(0, 0, 1) ? "YES" : "NO");
	}
}
min(x, y) { return x < y ? x : y; }
max(x, y) { return x > y ? x : y; }
ans;
main(a, b, c, i) {
	for (scanf("%*d"); ~scanf("%d%d%d", &a, &b, &c); ans = 0) {
		for (i = 0; i <= min(a, b / 2); i++) ans = max(ans, i + min(b - i * 2, c / 2));
		printf("%d\n", ans * 3);
	}
}
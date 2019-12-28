a[111], f = 1;
main(n, x) {
	for (scanf("%*d"); ~scanf("%d", &n); f = 1) {
		for (; n--; a[x] = 1) {
			scanf("%d", &x);
			if (a[x - 1] || a[x + 1]) f = 2;
		}
		memset(a, 0, sizeof a);
		printf("%d\n", f);
	}
}
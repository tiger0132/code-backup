main(x, y, z, a, b, c) {
	scanf("%d%d%d%d%d%d", &x, &y, &z, &a, &b, &c);
	if (a < x) return puts("NO"), 0;
	a -= x;
	if ((a += b) < y) return puts("NO");
	a -= y;
	if ((a += c) < z) return puts("NO");
	puts("YES");
}
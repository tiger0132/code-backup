p[111111], n, x, y, a;
f(x) { return x[p] ? x[p] = f(x[p]) : x; }
main() {
	for (scanf("%*d%d", &n); ~scanf("%d%d", &x, &y);)
		if (f(x) != f(y)) n--, p[f(x)] = f(y);
	printf("%d", n);
}
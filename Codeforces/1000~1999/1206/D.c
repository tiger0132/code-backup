typedef struct {
	int to, next;
} edge;
edge e[222222];
head[111111], cnt;
long long a[111111];
n, p[111111], ans = 1e9;
f(x) { return x[p] ? x[p] = f(x[p]) : x; }
$(x, y) {
	if ((x = f(x)) != (y = f(y))) x[p] = y;
}
ad(x, y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
	$(x, y);
}
dfs(s, t, f, d) {
	if (s == t) return d;
	for (int i = s[head], x; i; i = e[i].next)
		if (e[i].to != f && (x = dfs(e[i].to, t, s, d))) return x + 1;
	return 0;
}
main(n, i, j, x) {
	scanf("%d", &n);
	for (i = 0; i < n; i++) scanf("%lld", a + i);
	for (j = 0; j < 60; j++)
		for (i = 0; i < n; i++)
			if ((a[i] >> j) & 1) {
				if (f(j) != f(i + n))
					ad(i + n, j);
				else
					x = (dfs(i + n, j) + 1) / 2, ans = ans < x ? ans : x;
			}
	printf("%d\n", ans);
}
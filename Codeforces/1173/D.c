// typedef struct edge {
// 	int to, next;
// } e[444444];
deg[222222], fac[222222] = {1};
main(n, x, i, ans) {
	scanf("%d", &n), ans = n;
	for (i = 1; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % 998244353;
	while (~scanf("%d", &x)) deg[x]++;
	for (i = 1; i <= n; i++) ans = 1ll * ans * fac[deg[i]] % 998244353;
	printf("%d", ans);
}